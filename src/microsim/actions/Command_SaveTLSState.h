/****************************************************************************/
/// @file    Command_SaveTLSState.h
/// @author  Daniel Krajzewicz
/// @date    15 Feb 2004
/// @version $Id$
///
// Writes the state of the tls to a file
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
// copyright : (C) 2001-2007
//  by DLR (http://www.dlr.de/) and ZAIK (http://www.zaik.uni-koeln.de/AFS)
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef Command_SaveTLSState_h
#define Command_SaveTLSState_h


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <string>
#include <map>
#include <utils/helpers/Command.h>
#include <microsim/traffic_lights/MSTLLogicControl.h>


// ===========================================================================
// class declarations
// ===========================================================================
class MSTrafficLightLogic;
class OutputDevice;


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class Command_SaveTLSState
 * This action's execute command writes the state of the tls into a file
 */
class Command_SaveTLSState : public Command
{
public:
    /// Constructor
    Command_SaveTLSState(const MSTLLogicControl::TLSLogicVariants &logics,
                         OutputDevice &od);

    /// Destructor
    ~Command_SaveTLSState();

    /// Executes the action
    SUMOTime execute(SUMOTime currentTime);

private:
    /// The device to write to
    OutputDevice &myOutputDevice;

    /// The traffic light logic to use
    const MSTLLogicControl::TLSLogicVariants &myLogics;

};


#endif

/****************************************************************************/

