#include "RenderMan.h"
#include "Matrix.h"
#include "Color.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include "FrameBuffer.h"
#include <cstdarg>
#include <cmath>
#include <stdlib.h>

RtToken RI_PERSPECTIVE = "perspective";
RtToken RI_ORTHOGRAPHIC = "orthographic";

static char filename[20];
static int framenumber;

static bool activeContext = false;

static float fov;
static int xres, yres;
static float ratio;
static float hither, yon;
static Color currentColor;
static float opacity;

static int xsmpl, ysmpl;

static FrameBuffer* frameBuffer = NULL;
static Matrix projectionMatrix;
static Matrix currentTransform;
static Matrix worldToCameraTransform;

static RtShaderFunc surfaceShader = NULL;
static RtShaderFunc displacementShader = NULL;

void RiBegin(RtToken name) {
  if (name != RI_NULL) {
    printf("RiBegin: RiToken (%s) is not supported\n", name);
    exit(1);
  }

  // Set default variables  xres = 100;
  fov = (float)(M_PI/4);
  yres = 100;
  ratio = 1;
  hither = 1;
  yon = 1000;

  opacity = 1.0;
  currentColor.red = 255;
  currentColor.green = 255;
  currentColor.blue = 255;

  xsmpl = 4;
  ysmpl = 4;

  activeContext = true;
  RiIdentity();
}

void RiEnd(void) {
  if (!activeContext) {
    printf("RiEnd: No active context\n");
    exit(1);
  }

  // cleanup
  activeContext = false;
}

void RiFormat(RtInt xresolution, RtInt yresolution, RtFloat pixelaspectratio) {
  
  xres = xresolution;
  yres = yresolution;
  ratio = pixelaspectratio;
  frameBuffer = new FrameBuffer(xres, yres);
}

void RiProjection(RtToken name, ...) {

  va_list ap;
  va_start(ap, name);

  char * parametername = va_arg(ap, char*);

  if (strcmp(parametername, "fov") == 0) {
    fov = (float)(*va_arg(ap, float*) / 360 * M_PI);
  }
  
  if (strcmp(name, RI_PERSPECTIVE) == 0) {
    
    projectionMatrix = MatrixFactory::createPerspectiveProjection(
      fov, ratio, hither, yon
    );

  } else if ( strcmp(name, RI_ORTHOGRAPHIC) == 0) {
    projectionMatrix = MatrixFactory::createOrthogonalProjection(
      -xres/2, xres/2, yres/2, -yres/2, hither, yon
    );
  } else {
    printf("RiProjection: Projection (%s) is not supported\n", name);
    exit(1);
  }

}

void RiFrameAspectRatio(RtFloat frameaspectratio) {

  ratio = frameaspectratio;

}

void RiPixelSamples(RtFloat xsamples, RtFloat ysamples) {

  xsmpl = xsamples > 1.0 ? (int)xsamples : 1;
  ysmpl = ysamples > 1.0 ? (int)ysamples : 1;

} 

void RiDisplay(RtToken name, RtToken type, RtToken mode, ...) {

  (void) mode;

  if (strcmp(type, "file") == 0) {

    if (strlen(name) <= 19) {
      strncpy(filename, name, 19);
    } else {
      printf("RiDisplay: Filename '%s' is to long (max=19)\n", name);
      exit(1);
    }
  } else if (strcmp(type, "framebuffer") == 0) {
    printf("RiDisplay: Device '%s' is not implemented\n", name);
    exit(1);
  } else {
    printf("RiDisplay: Device '%s' is not supported\n", name);
    exit(1);
  }
  
}

void RiFrameBegin(RtInt frame) {
  frameBuffer->clear();
  framenumber = frame;
}

void RiFrameEnd(void) {
  frameBuffer->flush(framenumber);
}

void RiWorldBegin(void) {

  worldToCameraTransform = currentTransform;
  //RiIdentity();
  RiPerspective(fov);
  
}

void RiWorldEnd(void) {
  // Finish image
  //delete frameBuffer;
}

// Transforms
void RiTransformBegin(void) {
  // Noop since we dont have a stack
}

void RiTransformEnd(void) {
  // Noop since we dont have a stack
}

void RiIdentity(void) {
  currentTransform = MatrixFactory::createIdentity(4);
}

void RiTransform(RtMatrix transform) {
  currentTransform.transform(Matrix(transform));
}

void RiPerspective(RtFloat _fov) {
  (void) _fov;
}

void RiTranslate(RtFloat dx, RtFloat dy, RtFloat dz) {
  currentTransform.translate(dx, dy, dz);
}

void RiRotate(RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz) {

  angle = (float)((angle / 360.0) * 2*M_PI);

  if (dx == 1.0) {
    currentTransform.rotate(X, angle);
  }
  if (dy == 1.0) {
    currentTransform.rotate(Y, angle);
  }
  if (dz == 1.0) {
    currentTransform.rotate(Z, angle);
  }
}

void RiScale(RtFloat sx, RtFloat sy, RtFloat sz) {
  currentTransform.scale(sx, sy, sz);
}

void RiConcatTransform(RtMatrix transform) {

  currentTransform.transform(Matrix(transform));

}

void renderShape(Shape & shape) {
  shape.setOpacity(opacity);
  shape.setColor(currentColor.red, currentColor.green, currentColor.blue);
  shape.transform(currentTransform);
  shape.projectOnto(projectionMatrix);
  shape.homogenize();
  frameBuffer->draw(shape);

}

void RiSphere(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, ...) {
  Sphere sphere(radius, zmin, zmax, thetamax);
  renderShape(sphere);
}

void RiCone(RtFloat height, RtFloat radius, RtFloat thetamax, ...) {
  
  Cone cone(height, radius, thetamax);
  renderShape(cone);
}

void RiCylinder(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, ...) {

  Cylinder cylinder(radius, zmin, zmax, (float)((thetamax / 360.0) * (2*M_PI)));
  renderShape(cylinder);
}

void RiTorus(RtFloat majorradius, RtFloat minorradius, RtFloat phimin, RtFloat phimax, RtFloat thetamax, ...) {

  (void) majorradius;
  (void) minorradius;
  (void) phimin;
  (void) phimax;
  (void) thetamax;

}

void RiColor(RtColor color) {
  currentColor.red   = (uint8_t)(color[0] * 255);
  currentColor.green = (uint8_t)(color[1] * 255);
  currentColor.blue  = (uint8_t)(color[2] * 255);
}

void RiOpacity(RtColor color) {
  opacity = color[0];
}

// Not according to spec
void RiMakeTexture(char *picturename, RtInt slot) {
  (void) picturename;
  (void) slot;
}

void RiSurface(RtShaderFunc displacementFunc) {
  displacementShader = displacementFunc;
}

void RiDisplacement(RtShaderFunc surfaceFunc) {
  surfaceShader = surfaceFunc;
}

void RiShutter(RtFloat min, RtFloat max) {
  (void) min;
  (void) max;
}
