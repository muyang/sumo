/***************************************************************************
                          NIVisumParser_Connectors.cpp
              Parser for visum-connectors
                             -------------------
    project              : SUMO
    begin                : Thu, 14 Nov 2002
    copyright            : (C) 2002 by DLR/IVF http://ivf.dlr.de/
    author               : Daniel Krajzewicz
    email                : Daniel.Krajzewicz@dlr.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
namespace
{
    const char rcsid[] =
    "$Id$";
}
// $Log$
// Revision 1.8  2004/08/02 12:44:28  dkrajzew
// using Position2D instead of two doubles
//
// Revision 1.7  2004/01/12 15:36:08  dkrajzew
// node-building classes are now lying in an own folder
//
// Revision 1.6  2003/11/11 08:19:46  dkrajzew
// made the code a little bit more pretty
//
// Revision 1.5  2003/10/17 06:49:05  dkrajzew
// set the number of lanes of sources and sinks to three
//
// Revision 1.4  2003/07/07 08:30:59  dkrajzew
// adapted the importer to the new lane geometry description
//
// Revision 1.3  2003/04/01 15:26:14  dkrajzew
// insertion of nodes is now checked, but still unsafe; districts are always weighted
//
// Revision 1.2  2003/03/26 12:04:04  dkrajzew
// debugging for Vissim and Visum-imports
//
// Revision 1.1  2003/02/07 11:14:54  dkrajzew
// updated
//
//
/* =========================================================================
 * included modules
 * ======================================================================= */
#include <netbuild/NBHelpers.h>
#include <netbuild/nodes/NBNodeCont.h>
#include <netbuild/NBTypeCont.h>
#include <netbuild/NBDistrictCont.h>
#include <netbuild/NBDistrict.h>
#include <netbuild/nodes/NBNode.h>
#include <utils/convert/TplConvert.h>
#include <utils/convert/TplConvertSec.h>
#include "NIVisumLoader.h"
#include "NIVisumParser_Connectors.h"


/* =========================================================================
 * used namespaces
 * ======================================================================= */
using namespace std;


/* =========================================================================
 * method definitions
 * ======================================================================= */
NIVisumParser_Connectors::NIVisumParser_Connectors(NIVisumLoader &parent,
        const std::string &dataName)
    : NIVisumLoader::NIVisumSingleDataTypeParser(parent, dataName)
{
}


NIVisumParser_Connectors::~NIVisumParser_Connectors()
{
}


void
NIVisumParser_Connectors::myDependentReport()
{
    try {
        // get the source district
        string bez =
            NBHelpers::normalIDRepresentation(myLineParser.get("BezNr"));
        // get the destination node
        string node =
            NBHelpers::normalIDRepresentation(myLineParser.get("KnotNr"));
        NBNode *dest = NBNodeCont::retrieve(node);
        if(dest==0) {
            addError(
                string("The node '") + bez + string("' is not known."));
            return;
        }
        // get the weight of the connection
        double proz = getWeightedFloat("Proz");
        if(proz>0) {
            proz /= 100;
        } else {
            proz = 1;
        }
        // get the duration to wait
        double retard =
            TplConvertSec<char>::_2floatSec(
                myLineParser.get("t0-IV").c_str(), -1);
        // get the type;
        //  use a standard type with a large speed when a type is not given
        string type =
            NBHelpers::normalIDRepresentation(myLineParser.get("Typ"));

        double speed;
        int prio, nolanes;
        if(type.length()==0) {
            speed = 10000;
            nolanes = 1;
            prio = 0;
        } else {
            speed = NBTypeCont::getSpeed(type);
            nolanes = NBTypeCont::getNoLanes(type);
            prio = NBTypeCont::getPriority(type);
        }
        // add the connectors as an edge
        string id = bez + string("-") + node;
        // get the information whether this is a sink or a source
        string dir = myLineParser.get("Richtung");
        if(dir.length()==0) {
            dir = "QZ";
        }
        // build the source when needed
        if(dir.find('Q')!=string::npos) {
            NBNode *src = buildDistrictNode(bez, dest,
                NBEdge::EDGEFUNCTION_SOURCE);
            if(src==0) {
                addError(
                    string("The district '")
                    + bez + string("' is not known."));
                return;
            }
            NBEdge *edge = new NBEdge(id, id, src, dest, "VisumConnector",
                100, 3/*nolanes*/, 200.0, prio, NBEdge::LANESPREAD_RIGHT,
                NBEdge::EDGEFUNCTION_SOURCE);
            if(!NBEdgeCont::insert(edge)) {
                addError(
                    string("A duplicate edge id occured (ID='") + id
                    + string("')."));
            } else {
                NBDistrictCont::addSource(bez, edge, proz);
            }
        }
        // build the sink when needed
        if(dir.find('Z')!=string::npos) {
            NBNode *src = buildDistrictNode(bez, dest,
                NBEdge::EDGEFUNCTION_SINK);
            if(src==0) {
                addError(
                    string("The district '") + bez
                    + string("' is not known."));
                return;
            }
            id = string("-") + id;
            NBEdge *edge = new NBEdge(id, id, dest, src, "VisumConnector",
                100, 3/*nolanes*/, 2000.0, prio, NBEdge::LANESPREAD_RIGHT,
                NBEdge::EDGEFUNCTION_SINK);
            if(!NBEdgeCont::insert(edge)) {
                addError(
                    string("A duplicate edge id occured (ID='") + id
                    + string("')."));
            } else {
                NBDistrictCont::addSink(bez, edge, proz);
            }
        }
    } catch (OutOfBoundsException) {
        addError2("ANBINDUNG", "", "OutOfBounds");
    } catch (NumberFormatException) {
        addError2("ANBINDUNG", "", "NumberFormat");
    } catch (UnknownElement) {
        addError2("ANBINDUNG", "", "UnknownElement");
    }
}


NBNode *
NIVisumParser_Connectors::buildDistrictNode(const std::string &id,
                                            NBNode *dest,
                                            NBEdge::EdgeBasicFunction dir)
{
    // get the district
    NBDistrict *dist = NBDistrictCont::retrieve(id);
    if(dist==0) {
        return 0;
    }
    // get the coordinates of the new node
    double x = dest->getPosition().x()
        + (dist->getPosition().x() - dest->getPosition().x()) / 10;
    double y = dest->getPosition().y()
        + (dist->getPosition().y() - dest->getPosition().y()) / 10;
    // translate in dependence to the type
    if(dir==NBEdge::EDGEFUNCTION_SINK) {
        x += (dist->getPosition().y() - dest->getPosition().y()) / 100;
        y -= (dist->getPosition().x() - dest->getPosition().x()) / 100;
    } else {
        x -= (dist->getPosition().y() - dest->getPosition().y()) / 100;
        y += (dist->getPosition().x() - dest->getPosition().x()) / 100;
    }
    // build the id
    string nid;
    nid = id + "-" + dest->getID();
    if(dir==NBEdge::EDGEFUNCTION_SINK) {
        nid = "-" + nid;
    }
    // insert the node
    if(!NBNodeCont::insert(nid, Position2D(x, y))) {
        x += 0.1;
        y -= 0.1;
        if(!NBNodeCont::insert(nid, Position2D(x, y), dist)) {
            addError(
                "Ups, this should not happen: A district lies on a node.");
            return 0;
        }
    }
    // return the node
    return NBNodeCont::retrieve(nid);
}


/**************** DO NOT DEFINE ANYTHING AFTER THE INCLUDE *****************/
//#ifdef DISABLE_INLINE
//#include "NIVisumParser_Connectors.icc"
//#endif

// Local Variables:
// mode:C++
// End:


