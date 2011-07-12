/****************************************************************************/
/// @file    GUIVisualizationSettings.h
/// @author  Daniel Krajzewicz
/// @date    Sept 2002
/// @version $Id$
///
// Stores the information about how to visualize structures
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
// Copyright (C) 2001-2011 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef GUIVisualizationSettings_h
#define GUIVisualizationSettings_h


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <string>
#include <vector>
#include <map>
#include <utils/common/RGBColor.h>
#include <guisim/GUIEdge.h>
#include <guisim/GUILaneWrapper.h>
#include <guisim/GUIVehicle.h>


// ===========================================================================
// class declarations
// ===========================================================================
class BaseSchemeInfoSource;
class OutputDevice;


// ===========================================================================
// class definitions
// ===========================================================================

// cannot declare this as inner class because it needs to be used in forward
// declaration (@todo fix inclusion order by removing references to guisim!)
struct GUIVisualizationTextSettings {
    GUIVisualizationTextSettings(bool _show, float _size, RGBColor _color) :
            show(_show), size(_size), color(_color) {}

    bool show;
    float size;
    RGBColor color;

    bool operator==(const GUIVisualizationTextSettings &other) {
        return show == other.show &&
               size == other.size &&
               color == other.color;
    }
    bool operator!=(const GUIVisualizationTextSettings &other) {
        return !((*this) == other);
    }

    std::string print(const std::string& name) const {
        return name + "_show=\"" + toString(show) + "\" " +
               name + "_size=\"" + toString(size) + "\" " +
               name + "_color=\"" + toString(color) + "\" ";
    }
};

/**
 * @class GUIVisualizationSettings
 * @brief Stores the information about how to visualize structures
 */
class GUIVisualizationSettings {
public:

    /// @brief constructor
    GUIVisualizationSettings() throw();

    /// @brief The name of this setting
    std::string name;

    /// @brief Information whether antialiase shall be enabled
    bool antialiase;
    /// @brief Information whether dithering shall be enabled
    bool dither;

    /// @name Background visualization settings
    //@{

    /// @brief The background color to use
    RGBColor backgroundColor;
    /// @brief Information whether background decals (textures) shall be used
    bool showBackgroundDecals;
    /// @brief Information whether a grid shall be shown
    bool showGrid;
    /// @brief Information about the grid spacings
    SUMOReal gridXSize, gridYSize;
    //@}


    /// @name lane visualization settings
    //@{

#ifdef HAVE_MESOSIM
    /// @brief The mesoscopic edge colorer
    GUIEdge::Colorer edgeColorer;
#endif
    /// @brief The lane colorer
    GUILaneWrapper::Colorer laneColorer;
    /// @brief Information whether lane borders shall be drawn
    bool laneShowBorders;
    /// @brief Information whether link textures (arrows) shall be drawn
    bool showLinkDecals;
    /// @brief Information whether rails shall be drawn
    bool showRails;
    // Setting bundles for optional drawing names with size and color
    GUIVisualizationTextSettings edgeName, internalEdgeName, streetName;

    bool hideConnectors;
    //@}


    /// @name vehicle visualization settings
    //@{

    /// @brief The vehicle colorer
    GUIVehicle::Colorer vehicleColorer;
    /// @brief The quality of vehicle drawing
    int vehicleQuality;
    /// @brief The minimum size of vehicles to let them be drawn
    float minVehicleSize;
    /// @brief The vehicle exaggeration (upscale)
    float vehicleExaggeration;
    /// @brief Information whether vehicle blinkers shall be drawn
    bool showBlinker;
    /// @brief Information whether the lane change preference shall be drawn
    bool drawLaneChangePreference;
    // Setting bundles for optional drawing vehicle names
    GUIVisualizationTextSettings vehicleName;
    //@}


    /// @name junction visualization settings
    //@{

    /// @brief The junction visualization (color assignment) scheme
    int junctionMode;
    /// @brief Information whether a link's tls index shall be drawn
    bool drawLinkTLIndex;
    /// @brief Information whether a link's junction index shall be drawn
    bool drawLinkJunctionIndex;
    // Setting bundles for optional drawing junction names
    GUIVisualizationTextSettings junctionName, internalJunctionName;
    //@}


    /// @brief Information whether lane-to-lane arrows shall be drawn
    bool showLane2Lane;


    /// @name Additional structures visualization settings
    //@{

    /// @brief The additional structures visualization scheme
    int addMode;
    /// @brief The minimum size of additional structures to let them be drawn
    float minAddSize;
    /// @brief The additional structures exaggeration (upscale)
    float addExaggeration;
    // Setting bundles for optional drawing additional names
    GUIVisualizationTextSettings addName;
    //@}


    /// @name shapes visualization settings
    //@{

    /// @brief The minimum size of shapes to let them be drawn
    float minPOISize;
    /// @brief The additional shapes (upscale)
    float poiExaggeration;
    // Setting bundles for optional drawing poi names
    GUIVisualizationTextSettings poiName;
    //@}

    /// @brief Information whether the size legend shall be drawn
    bool showSizeLegend;

    /// @brief A temporary (used for a single view) information about a lane's width
    SUMOReal scale;

    /// @brief whether the application is in gaming mode or not
    bool gaming;

    /// @brief the current NETEDIT mode
    int editMode;

    /** @brief Writes the settings into an output device
     * @param[in] dev The device to write the settings into
     */
    void save(OutputDevice &dev) const throw(IOError);

    /** @brief Returns the number of the active lane (edge) coloring schme
     * @return number of the active scheme
     */
    size_t getLaneEdgeMode() const;

    /** @brief Returns the current lane (edge) coloring schme
     * @return current scheme
     */
    GUIColorScheme& getLaneEdgeScheme();

    /** @brief Assignment operator */
    bool operator==(const GUIVisualizationSettings &vs2);
};


#endif

/****************************************************************************/

