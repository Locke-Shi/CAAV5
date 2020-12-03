/**
* @quickReview GDR 04:03:02
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
// Sample code for : Geometric Modeler
// Mission         : Create a tetrahedron directly using the topological objects
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return Codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//                   4- Problem in the build of the body. See the trace for a detailed message
//                  10- The generated body has more than one domain 
//                  11- The domain has more than one cell
//                  12- The cell dimension is not 2
//                  13- There are not 4 faces  
//                  14- The geometry is not a face
//                  15- A face has not 3 edges                  
//
// Illustrates     : 1- Creation of the geometric factory
//                   2- Geometry creation:
//                      a- planes
//                      b- Pcurves
//                   3- Vertex Creation  
//                   4- Edge Creation
//                   5- Loop and Face Creation 
//                   6- Shell creation
//                   7- Volume creation
//                   8- Lump creation
//                   9- Body completion
//                  10- Scan of the body structure
//                  11 -factory close. 
//
// How to run it   : CAATobTetra            // to run whithout storing the NCGM file
//                   CAATobTetra  file.NCGM // to run and store the result in file.NCGM 
//=============================================================================

#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATMathPoint.h"          // Mathematical point

// GeometricObjects
#include "CATGeoFactory.h"         // Geometry factory
#include "CATCGMContainerMngt.h"   // Management of the geometry factory

#include "CATSurParam.h"           // Surface parameter
#include "CATCrvParam.h"           // Curve parameter
#include "CATCrvLimits.h"          // Limits on a curve 
#include "CATPlane.h"              // Geometric plane
#include "CATPLine.h"              // Line on a surface
#include "CATMacroPoint.h"         // Macro point (geometry of the vertex)
#include "CATPointOnEdgeCurve.h"   // Point on edge curve
#include "CATSimCurve.h"           // A particular type of edge curve 

// TopologicalObjects
#include "CATVertex.h"             // Vertex 
#include "CATEdge.h"               // Edge
#include "CATFace.h"               // Face 
#include "CATVolume.h"             // Volume
#include "CATShell.h"              // Shell
#include "CATLoop.h"               // Loop 
#include "CATBody.h"               // Body
#include "CATLump.h"               // Lump
#include "CATBoundaryIterator.h"   // Iterator on the bounding cells of a cell


// Error management
#include "CATError.h"              // errors
#include "CATErrorMacros.h"        // to catch errors 

//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
 int rc=0;
 if(2<iArgc) return (1);

 char *pFileName = 0;
 int  toStore = 0;
 if (2==iArgc) 
 {
    toStore = 1; 
    pFileName = iArgv[1];
 }

  //-----------------------------------------------------------------------------
  // 1-Initialize the factory 
  //-----------------------------------------------------------------------------
	
  CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
  if (NULL == piGeomFactory) return (1);

  //-----------------------------------------------------------------------------
  // 2- Create the geometry
  //-----------------------------------------------------------------------------

  // ----------- Creates the planes 

  CATPlane * piPlanexy = piGeomFactory->CreatePlane(CATMathPoint(),
                                                    CATMathPoint(1,0,0),
                                                    CATMathPoint(0,1,0));
  CATPlane * piPlaneyz = piGeomFactory->CreatePlane(CATMathPoint(),
                                                    CATMathPoint(0,1,0),
                                                    CATMathPoint(0,0,1));
  CATPlane * piPlanexz = piGeomFactory->CreatePlane(CATMathPoint(),
                                                    CATMathPoint(1,0,0),
                                                    CATMathPoint(0,0,1));
  CATPlane * piPlanec  = piGeomFactory->CreatePlane(CATMathPoint(10,0,0),
                                                    CATMathPoint(0,10,0),
                                                    CATMathPoint(0,0,10));
  // is all right?
  if (NULL==piPlanexy || NULL==piPlaneyz || NULL==piPlanexz || NULL==piPlanec) 
  {
    ::CATCloseCGMContainer(piGeomFactory);
    return (1);	
  }
  // ----------- Creates the PLines on each plane

  // PLines on Planexy
  CATSurParam Pxy0,Pxy1,Pxy2;
  // Gets the curve parameter corresponding to the mathematical point
  // This is only possible here, because we know that the Point is on the plane
  // If the surface were not canonical, or if the point were not on the surface,
  // we might use a projection operator.
  piPlanexy->GetParam(CATMathPoint(0 , 0,0),Pxy0); 
  piPlanexy->GetParam(CATMathPoint(10, 0,0),Pxy1);
  piPlanexy->GetParam(CATMathPoint(0 ,10,0),Pxy2);
  
  // Creates the plines from the parameters	
  CATPLine * piPLinexy01 = piGeomFactory->CreatePLine( Pxy0, Pxy1, piPlanexy );
  CATPLine * piPLinexy12 = piGeomFactory->CreatePLine( Pxy1, Pxy2, piPlanexy );
  CATPLine * piPLinexy20 = piGeomFactory->CreatePLine( Pxy2, Pxy0, piPlanexy );
		
  // PLines on Planeyz	
  CATSurParam Pyz0,Pyz1,Pyz2;
  piPlaneyz->GetParam(CATMathPoint(0 , 0, 0),Pyz0); 
  piPlaneyz->GetParam(CATMathPoint(0 ,10, 0),Pyz1);
  piPlaneyz->GetParam(CATMathPoint(0 , 0,10),Pyz2);
		
  CATPLine * piPLineyz01 = piGeomFactory->CreatePLine( Pyz0, Pyz1, piPlaneyz );
  CATPLine * piPLineyz12 = piGeomFactory->CreatePLine( Pyz1, Pyz2, piPlaneyz );
  CATPLine * piPLineyz20 = piGeomFactory->CreatePLine( Pyz2, Pyz0, piPlaneyz );
		
	// PLines on Planexz	
  CATSurParam Pxz0,Pxz1,Pxz2;
  piPlanexz->GetParam(CATMathPoint(0 , 0, 0),Pxz0); 
  piPlanexz->GetParam(CATMathPoint(10, 0, 0),Pxz1);
  piPlanexz->GetParam(CATMathPoint(0 , 0,10),Pxz2);
		
  CATPLine * piPLinexz01 = piGeomFactory->CreatePLine( Pxz0, Pxz1, piPlanexz );
  CATPLine * piPLinexz12 = piGeomFactory->CreatePLine( Pxz1, Pxz2, piPlanexz );
  CATPLine * piPLinexz20 = piGeomFactory->CreatePLine( Pxz2, Pxz0, piPlanexz );

  // PLines on Planec	
  CATSurParam Pc0,Pc1,Pc2;  
  piPlanec->GetParam(CATMathPoint(10,0,0),Pc0);                                   
  piPlanec->GetParam(CATMathPoint(0,10,0),Pc1);
  piPlanec->GetParam(CATMathPoint(0,0,10),Pc2);
		
  CATPLine * piPLinec01 = piGeomFactory->CreatePLine( Pc0, Pc1, piPlanec );
  CATPLine * piPLinec12 = piGeomFactory->CreatePLine( Pc1, Pc2, piPlanec );
  CATPLine * piPLinec20 = piGeomFactory->CreatePLine( Pc2, Pc0, piPlanec );
  // is all right?
  if (NULL==piPLineyz01 || NULL==piPLineyz12 || NULL==piPLineyz20 ||
      NULL==piPLinexy01 || NULL==piPLinexy12 || NULL==piPLinexy20 ||
      NULL==piPLinexz01 || NULL==piPLinexz12 || NULL==piPLinexz20 ||
      NULL==piPLinec01  || NULL==piPLinec12  || NULL==piPLinec20 )
  {
      ::CATCloseCGMContainer(piGeomFactory);
      return (1);	
  }				
		
  // ----------- Creates the Edge Curves, representing several PLines
  //
  CATLISTP(CATCurve)     curves;
  CATLISTP(CATCrvLimits) limits;
  CATListOfInt           orients;     
  CATCrvLimits           crvLim1,crvLim2;
  double resolution = piGeomFactory ->GetResolution();

  // Appends the first curve in of the sim curve 
  curves.Append(piPLinexy01);
  piPLinexy01->GetLimits(crvLim1);
  // Defines its limits
  limits.Append(&crvLim1);
  // Defines its relative orientation in the edge curve
  orients.Append(1);

  // The same for the second pline
  curves.Append(piPLinexz01);
  piPLinexy01->GetLimits(crvLim2);
  limits.Append(&crvLim2);
  orients.Append(1);

  // Now creates the sim curve
  CATSimCurve * piSimCurve01= piGeomFactory-> CreateSimCurve(curves,limits,orients,resolution);

  // The second sim curve
  piPLinexy12->GetLimits(*(limits[1]));
  curves[1]  = piPLinexy12;
  piPLinec01->GetLimits(*(limits[2]));
  curves[2]  = piPLinec01;
  CATSimCurve * piSimCurve12= piGeomFactory-> CreateSimCurve(curves,limits,orients,resolution);

  // The third sim curve
  curves[1] = piPLinexz20;
  piPLinexz20 ->GetLimits(*(limits[1]));
  curves[2] = piPLineyz20;
  piPLineyz20 ->GetLimits(*(limits[2]));
  CATSimCurve * piSimCurve30= piGeomFactory-> CreateSimCurve(curves,limits,orients,resolution);

 // The fourth sim curve		
  curves[1] = piPLineyz12;
  piPLineyz12 ->GetLimits(*(limits[1]));
  curves[2] = piPLinec12;
  piPLinec12 ->GetLimits(*(limits[2]));
  CATSimCurve * piSimCurve23= piGeomFactory-> CreateSimCurve(curves,limits,orients,resolution);

  // The fiveth sim curve
  curves[1] = piPLinexy20;
  piPLinexy20 ->GetLimits(*(limits[1]));
  curves[2] = piPLineyz01;
  piPLineyz01 ->GetLimits(*(limits[2]));
  orients[2] = -1;
  CATSimCurve * piSimCurve20= piGeomFactory-> CreateSimCurve(curves,limits,orients,resolution);

  // The sixth sim curve
  curves[1] = piPLinexz12;
  piPLinexz12 ->GetLimits(*(limits[1]));
  curves[2] = piPLinec20;
  piPLinec20 ->GetLimits(*(limits[2]));
  CATSimCurve * piSimCurve13= piGeomFactory-> CreateSimCurve(curves,limits,orients,resolution);
  // is all right?
  if (NULL==piSimCurve01 || NULL==piSimCurve12 || NULL==piSimCurve20 ||
      NULL==piSimCurve23 || NULL==piSimCurve30 || NULL==piSimCurve13 )
  {
     ::CATCloseCGMContainer(piGeomFactory);
     return (1);	
  }			
		
 // ----------- Creates the point on Edge Curves, limiting the Plines
  //
 // Poecs on edge curve 01
  CATCrvParam  crvParam;
  CATCrvLimits crvLimit;
  CATPointOnEdgeCurve *piPoec01Start=NULL,*piPoec01End=NULL;
  // Gets the limits of the first Pline
  piPLinexy01->GetLimits(crvLimit);
  // Defines the point on edge curve corresponding to the low limit
  crvLimit.GetLow(crvParam);
  piPoec01Start = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy01,crvParam,piSimCurve01);
  // Defines the point on edge curve corresponding to the high limit
  crvLimit.GetHigh(crvParam);
  piPoec01End   = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy01,crvParam,piSimCurve01);

// Poecs on edge curve 12	
  CATPointOnEdgeCurve *piPoec12Start=NULL,*piPoec12End=NULL;
  piPLinexy12->GetLimits(crvLimit);
  crvLimit.GetLow(crvParam);
  piPoec12Start = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy12,crvParam,piSimCurve12);
  crvLimit.GetHigh(crvParam);
  piPoec12End   = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy12,crvParam,piSimCurve12);

// Poecs on edge curve 20			
  CATPointOnEdgeCurve *piPoec20Start=NULL,*piPoec20End=NULL;
  piPLinexy20->GetLimits(crvLimit);
  crvLimit.GetLow(crvParam);  
  piPoec20Start = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy20,crvParam,piSimCurve20);
  crvLimit.GetHigh(crvParam);
  piPoec20End   = piGeomFactory->CreatePointOnEdgeCurve( piPLinexy20,crvParam,piSimCurve20);
		
// Poecs on edge curve 23
  CATPointOnEdgeCurve *piPoec23Start=NULL,*piPoec23End=NULL;
  piPLineyz12->GetLimits(crvLimit);
  crvLimit.GetLow(crvParam);
  piPoec23Start = piGeomFactory->CreatePointOnEdgeCurve( piPLineyz12,crvParam,piSimCurve23);
  crvLimit.GetHigh(crvParam);
  piPoec23End   = piGeomFactory->CreatePointOnEdgeCurve( piPLineyz12,crvParam,piSimCurve23);

// Poecs on edge curve 30		
  CATPointOnEdgeCurve *piPoec30Start=NULL,*piPoec30End=NULL;
  piPLineyz20->GetLimits(crvLimit);
  crvLimit.GetLow(crvParam);  
  piPoec30Start = piGeomFactory->CreatePointOnEdgeCurve( piPLineyz20,crvParam,piSimCurve30);
  crvLimit.GetHigh(crvParam);
  piPoec30End   = piGeomFactory->CreatePointOnEdgeCurve( piPLineyz20,crvParam,piSimCurve30);
		
// Poecs on edge curve 13
  CATPointOnEdgeCurve *piPoec13Start=NULL,*piPoec13End=NULL;		
  piPLinexz12->GetLimits(crvLimit);
  crvLimit.GetLow(crvParam);
  piPoec13Start = piGeomFactory->CreatePointOnEdgeCurve( piPLinexz12,crvParam,piSimCurve13);
  crvLimit.GetHigh(crvParam);
  piPoec13End   = piGeomFactory->CreatePointOnEdgeCurve( piPLinexz12,crvParam,piSimCurve13);
 // is all right?
  if (NULL==piPoec01Start || NULL==piPoec01End ||
      NULL==piPoec12Start || NULL==piPoec12End ||
      NULL==piPoec20Start || NULL==piPoec20End ||
      NULL==piPoec23Start || NULL==piPoec23End || 
      NULL==piPoec30Start || NULL==piPoec30End || 
      NULL==piPoec13Start || NULL==piPoec13End)
  {
	 ::CATCloseCGMContainer(piGeomFactory);
	 return (1);	
  }					
		
  // ----------- Creates the MacroPoints, representing several points
  //
  CATMacroPoint *piMacro0=NULL, *piMacro1=NULL, *piMacro2=NULL, *piMacro3=NULL; 
  CATLISTP(CATPoint) points;
  // Adds 3 points in edge curve per macro point, because there are 3 incident edges
  // at each vertex
  points.Append(piPoec01Start);
  points.Append(piPoec20End);
  points.Append(piPoec30End);
  piMacro0 = piGeomFactory->CreateMacroPoint(points);

  points[1] = piPoec01End;
  points[2] = piPoec12Start;
  points[3] = piPoec13Start;
  piMacro1 = piGeomFactory->CreateMacroPoint(points);
		
  points[1] = piPoec12End;
  points[2] = piPoec20Start;
  points[3] = piPoec23Start;
  piMacro2 = piGeomFactory->CreateMacroPoint(points);
		
  points[1] = piPoec23End;
  points[2] = piPoec30Start;
  points[3] = piPoec13End;
  piMacro3 = piGeomFactory->CreateMacroPoint(points);
  // is all right?
  if (NULL==piMacro0 || NULL==piMacro1 || NULL==piMacro2 || NULL==piMacro3 )
  {
    ::CATCloseCGMContainer(piGeomFactory);
    return (1);	
  }		
		
  // ----------- Creates the factory of the cells
  //
  CATBody * piTetra = piGeomFactory->CreateBody();
  // is all right?
  if (NULL==piTetra)
  {
	::CATCloseCGMContainer(piGeomFactory);
	return (1);	
  }		
		
  //-----------------------------------------------------------------------------
  // 3- Creates the vertices
  //-----------------------------------------------------------------------------

  CATVertex *piVertex0=NULL, *piVertex1=NULL, *piVertex2=NULL, *piVertex3=NULL; 
  piVertex0 = piTetra->CreateVertex();
  piVertex1 = piTetra->CreateVertex();
  piVertex2 = piTetra->CreateVertex();
  piVertex3 = piTetra->CreateVertex();
  // is all right?
  if (NULL==piVertex0 || NULL==piVertex1 ||NULL==piVertex2 ||NULL==piVertex3) 
  {
	::CATCloseCGMContainer(piGeomFactory);
	return (1);	
  }	
  // Associates with their geometry
  piVertex0->SetPoint(piMacro0);
  piVertex1->SetPoint(piMacro1);
  piVertex2->SetPoint(piMacro2);
  piVertex3->SetPoint(piMacro3);


  //-----------------------------------------------------------------------------
  // 4- Creates the edges
  //-----------------------------------------------------------------------------		
  //   Creates the edges, associates with the geometry;
  //   bounds them by the vertices
	
  CATEdge *piEdge01=NULL, *piEdge12=NULL, *piEdge20=NULL, 
	      *piEdge23=NULL, *piEdge30=NULL, *piEdge13=NULL; 
  piEdge01 = piTetra->CreateEdge();
  piEdge12 = piTetra->CreateEdge();
  piEdge20 = piTetra->CreateEdge();
  piEdge23 = piTetra->CreateEdge();
  piEdge30 = piTetra->CreateEdge();
  piEdge13 = piTetra->CreateEdge();
  // is all right?
  if (NULL==piEdge01 || NULL==piEdge12 ||NULL==piEdge20 ||
	  NULL==piEdge23 || NULL==piEdge30 || NULL==piEdge13)
  {
	::CATCloseCGMContainer(piGeomFactory);
	return (1);	
  }	
  // Sets the geometry of Edge01: the sim curve, and the relative orientation
  // between the sim curve and the edge
  piEdge01->SetCurve(piSimCurve01,CATOrientationPositive);
  // Bounds Edge01 by Vertex0,    
  piEdge01->AddBoundingCell(piVertex0,
                            CATSideLeft,    //Vertex0 is the start vertex (CATSideLeft)
                            NULL,           //Vertex0 does not belong to any domain (NULL)
                            piPoec01Start); //The corresponding geometry of Vertex0 in the context of 
                                            // the edge Edge01 is Poec01Start
  // Bounds Edge01 by Vertex1, 
  //    Vertex1 is the end vertex (CATSideRight)
  //    Vertex0 does not belong to any domain (NULL)
  //    The corresponding geometry of Vertex1 in the context of the edge Edge01 is Poec01End
  piEdge01->AddBoundingCell(piVertex1,CATSideRight,NULL,piPoec01End);
		
  piEdge12->SetCurve(piSimCurve12,CATOrientationPositive);
  piEdge12->AddBoundingCell(piVertex1,CATSideLeft,NULL,piPoec12Start);
  piEdge12->AddBoundingCell(piVertex2,CATSideRight,NULL,piPoec12End);
	
  piEdge20->SetCurve(piSimCurve20,CATOrientationPositive);
  piEdge20->AddBoundingCell(piVertex2,CATSideLeft,NULL,piPoec20Start);
  piEdge20->AddBoundingCell(piVertex0,CATSideRight,NULL,piPoec20End);

  piEdge23->SetCurve(piSimCurve23,CATOrientationPositive);
  piEdge23->AddBoundingCell(piVertex2,CATSideLeft,NULL,piPoec23Start);
  piEdge23->AddBoundingCell(piVertex3,CATSideRight,NULL,piPoec23End);	

  piEdge30->SetCurve(piSimCurve30,CATOrientationPositive);
  piEdge30->AddBoundingCell(piVertex3,CATSideLeft,NULL,piPoec30Start);
  piEdge30->AddBoundingCell(piVertex0,CATSideRight,NULL,piPoec30End);

  piEdge13->SetCurve(piSimCurve13,CATOrientationPositive);
  piEdge13->AddBoundingCell(piVertex1,CATSideLeft,NULL,piPoec13Start);
  piEdge13->AddBoundingCell(piVertex3,CATSideRight,NULL,piPoec13End);

  //-----------------------------------------------------------------------------
  // 5- Creates the loops and faces
  //-----------------------------------------------------------------------------	
		
  CATFace *piFacexy=NULL, *piFaceyz=NULL, *piFacexz=NULL, *piFacec=NULL; 
  piFacexy = piTetra->CreateFace();
  piFaceyz = piTetra->CreateFace();
  piFacexz = piTetra->CreateFace();
  piFacec  = piTetra->CreateFace();
  CATLoop *piLoopxy=NULL, *piLoopyz=NULL, *piLoopxz=NULL, *piLoopc=NULL; 
  // The loops define external boundary of the faces (CATLocationOuter)
  piLoopxy = piTetra->CreateLoop(CATLocationOuter);
  piLoopyz = piTetra->CreateLoop(CATLocationOuter);
  piLoopxz = piTetra->CreateLoop(CATLocationOuter);
  piLoopc  = piTetra->CreateLoop(CATLocationOuter);
  // is all right?
  if (NULL==piFacexy || NULL==piFaceyz ||NULL==piFacexz || NULL==piFacec ||
      NULL==piLoopxy || NULL==piLoopyz ||NULL==piLoopxz || NULL==piLoopc)
  {
	::CATCloseCGMContainer(piGeomFactory);
	return (1);	
  }	

  // Face xy
  // Defines the external boundary of Facexy
  piFacexy->AddDomain(piLoopxy); 
  // Associates with the geometry. 
  // The orientation of the face and its geometry are opposite (CATOrientationNegative). 
  piFacexy->SetSurface(piPlanexy,CATOrientationNegative);
  // The first bounding edge Edge20
  // The matter is at the right side (CATSideRight)
  // The edge must be included in the Loopxy loop
  // The geometry of Edge20 in the context of Facexy is PLinexy20
  piFacexy->AddBoundingCell(piEdge20,CATSideRight,piLoopxy,piPLinexy20);
  piFacexy->AddBoundingCell(piEdge12,CATSideRight,piLoopxy,piPLinexy12);
  piFacexy->AddBoundingCell(piEdge01,CATSideRight,piLoopxy,piPLinexy01);
  // Declares that the loop is finished
  piLoopxy->Done();
		
  // Faceyz  
  piFaceyz->AddDomain(piLoopyz); 
  // Associates with the geometry and bounds the face
  piFaceyz->SetSurface(piPlaneyz,CATOrientationNegative);
  piFaceyz->AddBoundingCell(piEdge30,CATSideRight,piLoopyz,piPLineyz20);
  piFaceyz->AddBoundingCell(piEdge23,CATSideRight,piLoopyz,piPLineyz12);
  piFaceyz->AddBoundingCell(piEdge20,CATSideLeft,piLoopyz,piPLineyz01);
  piLoopyz->Done();// The loop is finished!
		
  // Facexz	
  piFacexz->AddDomain(piLoopxz); 
  // Associates with the geometry and bounds the face
  piFacexz->SetSurface(piPlanexz);
  piFacexz->AddBoundingCell(piEdge01,CATSideLeft,piLoopxz,piPLinexz01);
  piFacexz->AddBoundingCell(piEdge13,CATSideLeft,piLoopxz,piPLinexz12);
  piFacexz->AddBoundingCell(piEdge30,CATSideLeft,piLoopxz,piPLinexz20);					
  piLoopxz->Done();// The loop is finished!
		
  // Facec
  piFacec->AddDomain(piLoopc); 
  // Associates with the geometry and bounds the face
  piFacec->SetSurface(piPlanec);
  piFacec->AddBoundingCell(piEdge12,CATSideLeft,piLoopc,piPLinec01);
  piFacec->AddBoundingCell(piEdge23,CATSideLeft,piLoopc,piPLinec12);
  piFacec->AddBoundingCell(piEdge13,CATSideRight,piLoopc,piPLinec20);
  piLoopc->Done();// The loop is finished!
		
  //-----------------------------------------------------------------------------
  // 6- Creates the shell
  //-----------------------------------------------------------------------------	
  CATShell * piShell = NULL;
  // The shell is the external boundary of a volume (CATLocationOuter)
  // To create a skin body, use CATLocationIn3DSpace, and directly attach the shell
  // to the body; also add the cells in the shell (AddCell)
  piShell = piTetra->CreateShell(CATLocationOuter);

  //-----------------------------------------------------------------------------
  // 7- Creates the volume
  //-----------------------------------------------------------------------------	
  CATVolume * piVolume = NULL;
  piVolume = piTetra->CreateVolume();	
  // is all right?
  if (NULL==piShell || NULL==piVolume )
  {
	::CATCloseCGMContainer(piGeomFactory);
	return (1);	
  }	
  // Adds the shell
  piVolume->AddDomain(piShell);

  // Bounds by the faces and add them in the shell at the same time
  // To define a volume, the shell orientation points to the volume inside 
  piVolume->AddBoundingCell(piFacexy, CATSideRight, piShell, piPlanexy);
  piVolume->AddBoundingCell(piFacexz, CATSideRight, piShell, piPlanexz);
  piVolume->AddBoundingCell(piFaceyz, CATSideRight, piShell, piPlaneyz);
  piVolume->AddBoundingCell(piFacec, CATSideRight, piShell, piPlanec);

  //-----------------------------------------------------------------------------
  // 8- Creates the lump
  //-----------------------------------------------------------------------------
  CATLump * piLump = NULL;
  piLump = piTetra->CreateLump();
  if (NULL==piShell || NULL==piVolume )
  {
	 ::CATCloseCGMContainer(piGeomFactory);
		return (1);	
  }
  // Adds the volume
  piLump->AddCell(piVolume);

  //-----------------------------------------------------------------------------
  // 9- Completes the Body 
  //-----------------------------------------------------------------------------
  piTetra->AddDomain(piLump);
  CATTry    // to catch an error
  {
	piTetra->Completed();
  }
  CATCatch(CATError,error)
  { 
    cout << (error->GetNLSMessage()).ConvertToChar()<<endl;
    rc=4;
  }
  CATEndTry

  //-----------------------------------------------------------------------------
  // 10- Scans the topological structure
  //-----------------------------------------------------------------------------
  // The number of domains of the tetrahedron  --> 1 lump
  CATLONG32 nbDomain = piTetra ->GetNbDomains();
  if (1!=nbDomain) 
  {
	::CATCloseCGMContainer(piGeomFactory);
	return (10);
  }
  CATDomain * piDomain = NULL;
  piDomain = piTetra->GetDomain(1);
  if (NULL==piDomain)
  {
	::CATCloseCGMContainer(piGeomFactory);
	return (1);	
  }	

  // The number of volumes of the tetrahedron  --> 1 volume
  CATLISTP(CATCell) listCells;
  piDomain ->GetAllCells(listCells, 3 );
  int nbCells = listCells.Size();
  if (1 != nbCells)
  {
	::CATCloseCGMContainer(piGeomFactory);
	return (11);
  }


  CATCell * piVolumeCell = listCells[1];
  if (NULL==piVolumeCell)
  {
	::CATCloseCGMContainer(piGeomFactory);
	return (1);	
  }	
  // Cleans the list (but not the objects!)
  listCells.RemoveAll();

  // The number of shells of the volume  --> 1 external bounding shell
  nbDomain = piVolumeCell->GetNbDomains();
  piDomain = piVolumeCell->GetDomain(1);
  if (NULL==piDomain)
  {
	::CATCloseCGMContainer(piGeomFactory);
	return (1);	
  }	
  // It is a shell, because it is made of faces (dimension 2) .
  short dimShell = piDomain->GetLowDimension();
  if ( 2 != dimShell )
  {
	::CATCloseCGMContainer(piGeomFactory);
	return (12);
  }

  // 4 faces in the shell
  piDomain ->GetAllCells(listCells,dimShell);
  nbCells = listCells.Size();
  if (4!=nbCells)
  {
	::CATCloseCGMContainer(piGeomFactory);
	return (13);
  }

  // Recovers the geometry of the faces
	
  for (int i=1;i<=nbCells;i++)
  {
	 CATCell * pLocalCell = listCells[i];
	 CATOrientation ori;
     if (NULL==pLocalCell)
     {
	   ::CATCloseCGMContainer(piGeomFactory);
	   return (1);	
     }	
    // Recovers the geometry
	CATGeometry * piGeom = pLocalCell->GetGeometry(&ori);
    if (NULL==piGeom)
    {
	  ::CATCloseCGMContainer(piGeomFactory);
	  return (1);	
    }	
    // Is the geometry of Plane type?
	if (NULL == (piGeom->IsATypeOf(CATPlaneType)) ) // the geometry is a plane!...
	{
	  ::CATCloseCGMContainer(piGeomFactory);
	  return (14);
	}
	// Another way to retrieve the cells: use a boundary iterator
	CATBoundaryIterator  *  pBoundaryIt =  pLocalCell->CreateBoundaryIterator();
    if (NULL==pBoundaryIt)
    {
	  ::CATCloseCGMContainer(piGeomFactory);
	  return (1);	
    }

	CATSide side;
	CATCell*  piBcell = NULL;
	int nbEdges=0;
    while ((piBcell=pBoundaryIt->Next(&side,&piDomain)) != NULL)      
	{
       nbEdges = nbEdges+1;      
	}
	delete pBoundaryIt;
	pBoundaryIt=NULL;
    
	// There must be three edges for each faces ...
	if (3!=nbEdges)
	{
	   ::CATCloseCGMContainer(piGeomFactory);
	   return (15);
    }

  }


  //-----------------------------------------------------------------------------
  // 11-Writes the model
  //-----------------------------------------------------------------------------
  if(1==toStore)
  {
#ifdef _WINDOWS_SOURCE
	 ofstream filetowrite(pFileName, ios::binary ) ;
#else
	 ofstream filetowrite(pFileName,ios::out,filebuf::openprot) ;
#endif

   ::CATSaveCGMContainer(piGeomFactory,filetowrite);
   filetowrite.close();
  }			

  //
  // Closes the container
  //
	
  ::CATCloseCGMContainer(piGeomFactory);
	

	return (rc);
}


