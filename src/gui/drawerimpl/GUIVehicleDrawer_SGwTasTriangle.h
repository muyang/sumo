#ifndef GUIVehicleDrawer_SGwTasTriangle_h
#define GUIVehicleDrawer_SGwTasTriangle_h
//---------------------------------------------------------------------------//
//                        GUIVehicleDrawer_SGwTasTriangle.cpp -
//  Class for drawing vehicles on simple geometry with tooltips as triangles
//                           -------------------
//  project              : SUMO - Simulation of Urban MObility
//  begin                : Tue, 02.09.2003
//  copyright            : (C) 2003 by Daniel Krajzewicz
//  organisation         : IVF/DLR http://ivf.dlr.de
//  email                : Daniel.Krajzewicz@dlr.de
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//---------------------------------------------------------------------------//
// $Log$
// Revision 1.9  2006/07/06 06:26:45  dkrajzew
// added blinker visualisation and vehicle tracking (unfinished)
//
// Revision 1.8  2006/01/09 11:50:21  dkrajzew
// new visualization settings implemented
//
// Revision 1.7  2005/10/07 11:36:48  dkrajzew
// THIRD LARGE CODE RECHECK: patched problems on Linux/Windows configs
//
// Revision 1.6  2005/09/22 13:30:40  dkrajzew
// SECOND LARGE CODE RECHECK: converted doubles and floats to SUMOReal
//
// Revision 1.5  2005/09/15 11:05:29  dkrajzew
// LARGE CODE RECHECK
//
// Revision 1.4  2005/04/29 11:10:58  dkrajzew
// codestyle adapted
//
// Revision 1.3  2005/04/27 09:44:26  dkrajzew
// level3 warnings removed
//
// Revision 1.2  2003/09/17 06:45:11  dkrajzew
// some documentation added/patched
//
// Revision 1.1  2003/09/05 14:50:39  dkrajzew
// implementations of artefact drawers moved to folder "drawerimpl"
//
/* =========================================================================
 * compiler pragmas
 * ======================================================================= */
#pragma warning(disable: 4786)


/* =========================================================================
 * included modules
 * ======================================================================= */
#ifdef HAVE_CONFIG_H
#ifdef WIN32
#include <windows_config.h>
#else
#include <config.h>
#endif
#endif // HAVE_CONFIG_H

#include "GUIBaseVehicleDrawer.h"


/* =========================================================================
 * class declarations
 * ======================================================================= */
class GUILaneWrapper;
class GUIVehicle;


/* =========================================================================
 * class definitions
 * ======================================================================= */
/**
 * Draws vehicles as coloured triangles
 */
class GUIVehicleDrawer_SGwTasTriangle :
    public GUIBaseVehicleDrawer {
public:
    /// constructor
    GUIVehicleDrawer_SGwTasTriangle(std::vector<GUIEdge*> &edges);

    /// destructor
    ~GUIVehicleDrawer_SGwTasTriangle();

private:
    void drawLanesVehicles(GUILaneWrapper &lane,
        GUIBaseColorer<GUIVehicle> &colorer, float upscale, bool showBlinker);

    void drawVehicle(const GUIVehicle &vehicle,
        SUMOReal posX, SUMOReal posY, SUMOReal rot,
        GUIBaseColorer<GUIVehicle> &colorer, float upscale);

};


/**************** DO NOT DEFINE ANYTHING AFTER THE INCLUDE *****************/

#endif

// Local Variables:
// mode:C++
// End:

