#ifndef _RENDERMAN_H_
#define _RENDERMAN_H_

typedef short RtBoolean;
typedef int RtInt;
typedef float RtFloat;


typedef char *RtToken;
#define RI_NULL ((RtToken)0)

extern const RtToken RI_PERSPECTIVE, RI_ORTHOGRAPHIC;

typedef RtFloat RtColor[3];
typedef RtFloat RtMatrix[4][4];
typedef RtFloat RtPoint[3];

// Not part of the spec
typedef void (*RtShaderFunc)(void);


void RiBegin(RtToken name);
void RiEnd(void);
void RiFormat(RtInt xresolution, RtInt yresolution, RtFloat pixelaspectratio); 
void RiProjection(RtToken name, ...);
void RiFrameAspectRatio(RtFloat frameaspectratio); 
void RiPixelSamples(RtFloat xsamples, RtFloat ysamples); 
void RiDisplay(RtToken name, RtToken type, RtToken mode, ...);
void RiFrameBegin(RtInt frame);
void RiFrameEnd(void);
void RiWorldBegin(void);
void RiWorldEnd(void);

// Transforms
void RiTransformBegin(void);
void RiTransformEnd(void);
void RiIdentity(void);
void RiTransform(RtMatrix transform);
void RiPerspective(RtFloat fov);
void RiTranslate(RtFloat dx, RtFloat dy, RtFloat dz);
void RiRotate(RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz);
void RiScale(RtFloat sx, RtFloat sy, RtFloat sz);
void RiConcatTransform(RtMatrix transform);

void RiSphere(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, ...);
void RiCone(RtFloat height, RtFloat radius, RtFloat thetamax, ...);
void RiCylinder(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, ...);
void RiTorus(RtFloat majorradius, RtFloat minorradius, RtFloat phimin, RtFloat phimax, RtFloat thetamax, ...);

void RiColor(RtColor color);
void RiOpacity(RtColor color);
// Not according to spec
void RiMakeTexture(char *picturename, RtInt slot);
void RiSurface(RtShaderFunc displacementFunc);
void RiDisplacement(RtShaderFunc surfaceFunc);
// ---

void RiShutter(RtFloat min, RtFloat max);

#endif /* _RENDERMAN_H_ */
