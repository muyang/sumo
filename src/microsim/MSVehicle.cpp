/***************************************************************************
                          MSVehicle.C  -  Base for all
                          micro-simulation Vehicles.
                             -------------------
    begin                : Mon, 05 Mar 2001
    copyright            : (C) 2001 by ZAIK http://www.zaik.uni-koeln.de/AFS
    author               : Christian Roessel
    email                : roessel@zpr.uni-koeln.de
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
// Revision 1.3  2002/10/16 17:33:10  dkrajzew
// error in moveCritical yielding in collisions removed
//
// Revision 1.2  2002/10/16 16:45:41  dkrajzew
// debugged
//
// Revision 1.1  2002/10/16 14:48:26  dkrajzew
// ROOT/sumo moved to ROOT/src
//
// Revision 1.21  2002/09/25 17:14:42  roessel
// MeanData calculation and output implemented.
//
// Revision 1.20  2002/07/31 17:33:01  roessel
// Changes since sourceforge cvs request.
//
// Revision 1.23  2002/07/31 14:42:34  croessel
// Use of new VehicleType methods.
//
// Revision 1.22  2002/07/24 16:33:49  croessel
// New methods isInsertTimeHeadWayCond() and isInsertBrakeCond() to check
// the Krauss conditions during emit/laneChange.
//
// Revision 1.21  2002/07/16 17:50:36  croessel
// Removed debug code.
//
// Revision 1.20  2002/07/03 15:57:11  croessel
// Redundant code removal.
// New methods isSafeChange, hasSafeGap, safeEmitGap instead of safeGap.
// Removed safeLaneChangeGap, not used.
// New method vNeighEqualPos for "don't overtake on the right".
// move() respects now neighbours taht shouldn't be overtaken.
//
// Revision 1.19  2002/06/25 10:53:36  croessel
// Little mistake in destructor.
//
// Revision 1.18  2002/06/25 10:41:17  croessel
// safeGap using fabs is not the answer to collisions. Removing it.
//
// Revision 1.17  2002/06/21 10:59:09  dkrajzew
// inclusion of .cpp-files in .cpp files removed
//
// Revision 1.16  2002/06/20 13:44:58  dkrajzew
// safeGap is now using fabs
//
// Revision 1.15  2002/06/20 08:00:59  dkrajzew
// template and .cpp inclusion inserted due to problems with MSVC++; should
// be revalidated and removed as soon as possible
//
// Revision 1.14  2002/06/19 15:09:12  croessel
// Changed *Gap methods to check for timeheadway < deltaT states.
//
// Revision 1.13  2002/06/11 19:38:22  croessel
// Bugfix: in safeGap(), vDecel should be max(...), not
// min(...). Otherwise gap is always < 0 and LaneChanger will almost
// always allow a change. This may lead to collisions in the next
// timesteps.
//
// Revision 1.12  2002/06/06 07:21:10  croessel
// Changed inclusion from .iC to .icc
//
// Revision 1.11  2002/05/29 17:06:03  croessel
// Inlined some methods. See the .icc files.
//
// Revision 1.10  2002/05/17 13:23:36  croessel
// Changed novehicles to MSNet::noVehicles
//
// Revision 1.9  2002/05/17 13:04:24  croessel
// Added _SPEEDCHECK code in all move-methos.
// Added upper bound (= vaacel) for vSafe in nextState().
// nextStateCompete():
// - Removed vMax and vLaneMax, they are already considered in vaccel().
// - Calculate nextPos with vNext instead of vSafe.
// New method laneChangeBrake2much() added.
//
// Revision 1.8  2002/05/08 13:24:21  croessel
// safeGap(): vDecel shouldn't be less than 0.
//
// Revision 1.7  2002/05/08 11:36:26  croessel
// destReached() changed to allow routes to include the destination-edge
// several times before reaching the destination.
//
// Revision 1.6  2002/04/24 15:22:08  croessel
// Bugfix: changed myType->decel() into myType->accel() in dadwle().
//
// Revision 1.5  2002/04/18 15:05:18  croessel
// In nextStateCompete(): Returns now correct position instead of 0.
//
// Revision 1.4  2002/04/18 14:30:24  croessel
// Bug in Revision 1.3 changes. Return State( pos, speed = 0 ) instead of
// myState.
//
// Revision 1.3  2002/04/17 10:58:24  croessel
// Introduced dontMoveGap to handle floating-point-inaccuracy. Vehicles
// will keep their state if gap2pred is smaller.
//
// Revision 1.2  2002/04/11 15:25:56  croessel
// Changed float to double.
//
// Revision 1.1.1.1  2002/04/08 07:21:23  traffic
// new project name
//
// Revision 2.4  2002/03/20 16:02:23  croessel
// Initialisation and update of allowedLanes-container fixed.
//
// Revision 2.3  2002/03/13 17:44:38  croessel
// Assert removed because it causes not intended crashes for
// YIELD_ON_SUCC.
//
// Revision 2.2  2002/03/13 17:42:19  croessel
// In nextState() we need to dawdle _before_ we set the new state.
//
// Revision 2.1  2002/03/13 16:56:35  croessel
// Changed the simpleOutput to XMLOutput by introducing nested classes
// XMLOut. Output is now indented.
//
// Revision 2.0  2002/02/14 14:43:19  croessel
// Bringing all files to revision 2.0. This is just cosmetics.
//
// Revision 1.14  2002/02/05 13:51:53  croessel
// GPL-Notice included.
// In *.cpp files also config.h included.
//
// Revision 1.13  2002/02/05 11:52:11  croessel
// Changed method vAccel() to accelState().
// Introduced new mezhods for lane-change:
// State::advantage()
// onAllowed()
// overlap()
// congested()
//
// Revision 1.12  2002/02/01 13:57:07  croessel
// Changed methods and members bmax/dmax/sigma to more meaningful names
// accel/decel/dawdle.
//
// Revision 1.11  2002/01/31 13:53:08  croessel
// Assertion in move() added.
//
// Revision 1.10  2002/01/24 18:29:43  croessel
// New and modified gap-methods: interactionDist renamed to brakeGap,
// interactionGap introduced and calculation of gaps fixed.
//
// Revision 1.9  2002/01/16 10:07:50  croessel
// Modified some speed calculations to the use of MSNet::deltaT() instead
// of myTau.
//
// Revision 1.8  2001/12/20 14:50:07  croessel
// new method: id() (moved from .h)
//
// Revision 1.7  2001/12/13 14:11:58  croessel
// Introduction of MSVehicle::State methods.
//
// Revision 1.6  2001/12/06 13:16:41  traffic
// speed computation added (use -D _SPEEDCHECK)
//
// Revision 1.5  2001/11/21 15:25:13  croessel
// Numerous changes during debug session.
//
// Revision 1.4  2001/11/15 17:17:36  croessel
// Outcommented the inclusion of the inline *.iC files. Currently not needed.
// Vehicle-State introduced. Simulation is now independant of vehicle's
// speed. Still, the position is fundamental, also a gap between
// vehicles. But that's it.
//
// Revision 1.3  2001/11/14 15:47:34  croessel
// Merged the diffs between the .C and .cpp versions. Numerous changes
// in MSLane, MSVehicle and MSJunction.
//
// Revision 1.2  2001/11/14 10:49:07  croessel
// CR-line-end removed.
//
// Revision 1.1  2001/10/24 07:17:13  traffic
// new extension
//
// Revision 1.6  2001/10/23 09:31:41  traffic
// parser bugs removed
//
// Revision 1.4  2001/09/06 15:35:50  croessel
// Added operator<< to class MSVehicle for simple text output and minor
// changes.
//
// Revision 1.3  2001/07/25 12:17:59  traffic
// CC problems with make_pair repaired
//
// Revision 1.2  2001/07/16 12:55:47  croessel
// Changed id type from unsigned int to string. Added string-pointer
// dictionaries and dictionary methods.
//
// Revision 1.1.1.1  2001/07/11 15:51:13  traffic
// new start
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include "MSVehicle.h"
#include "MSLane.h"
#include "MSEdge.h"
#include "MSVehicleType.h"
#include "MSNet.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;


// Init static member.
MSVehicle::DictType MSVehicle::myDict;
double MSVehicle::myTau = 1;

// It is possible to get collisions because of arithmetic-inaccuracy
// at small gaps. Therefore we introduce "dontMoveGap"; if gap2pred is
// smaller, than vehicle will keep it's state.
const double dontMoveGap = 0.01;

/////////////////////////////////////////////////////////////////////////////

MSVehicle::State::State() : myPos( 0 ), mySpeed( 0 )
{
}

/////////////////////////////////////////////////////////////////////////////

MSVehicle::State::State( const State& state )
{
    myPos = state.myPos;
    mySpeed = state.mySpeed;
}

/////////////////////////////////////////////////////////////////////////////

MSVehicle::State&
MSVehicle::State::operator=( const State& state )
{
    myPos   = state.myPos;
    mySpeed = state.mySpeed;
    return *this;
}

/////////////////////////////////////////////////////////////////////////////

bool
MSVehicle::State::operator!=( const State& state )
{
    return ( myPos   != state.myPos ||
             mySpeed != state.mySpeed );
}

/////////////////////////////////////////////////////////////////////////////

double
MSVehicle::State::pos() const
{
    return myPos;
}

/////////////////////////////////////////////////////////////////////////////

void
MSVehicle::State::setPos( double pos )
{
    assert( pos >= 0 );
    myPos = pos;
}

/////////////////////////////////////////////////////////////////////////////

bool
MSVehicle::State::advantage( const State& preferState,
                             const State& compareState )
{
    return preferState.mySpeed >= compareState.mySpeed;
}

/////////////////////////////////////////////////////////////////////////////

MSVehicle::State::State( double pos, double speed ) :
    myPos( pos ), mySpeed( speed )
{
}

/////////////////////////////////////////////////////////////////////////////

bool departTimeSortCrit( const MSVehicle* x, const MSVehicle* y )
{
    return x->myDesiredDepart < y->myDesiredDepart;
}

/////////////////////////////////////////////////////////////////////////////

MSVehicle::~MSVehicle()
{
    //myWaitingPersons.clear();
}

/////////////////////////////////////////////////////////////////////////////

MSVehicle::MSVehicle( string id,
                      MSNet::Route* route,
                      MSNet::Time departTime,
                      const MSVehicleType* type ) :
    myID(id),
    myState(),
    myRoute(route),
    myCurrEdge(0),
    myAllowedLanes(0),
    myDesiredDepart(departTime),
    myType(type),
//      myMeanData( 3 ),
    myMeanData( MSNet::getInstance()->getNDumpIntervalls() +
                MSNet::getInstance()->withGUI() ),
    myLane( 0 )
{
}

/////////////////////////////////////////////////////////////////////////////

MSVehicle::State
MSVehicle::state() const
{
    return myState;
}

/////////////////////////////////////////////////////////////////////////////

MSLane&
MSVehicle::departLane()
{
    myCurrEdge = myRoute->begin();
    myAllowedLanes = ( *myCurrEdge )->allowedLanes( **( myCurrEdge + 1 ) );
    return (*myCurrEdge)->departLane();
}

/////////////////////////////////////////////////////////////////////////////

MSNet::Time
MSVehicle::desiredDepart() const
{
    return myDesiredDepart;
}

/////////////////////////////////////////////////////////////////////////////

const MSEdge*
MSVehicle::succEdge(unsigned int nSuccs) const
{
    if ( hasSuccEdge( nSuccs ) ) {
        return *( myCurrEdge + nSuccs );
    }
    else {
        return 0;
    }
}

/////////////////////////////////////////////////////////////////////////////

bool
MSVehicle::hasSuccEdge(unsigned int nSuccs) const
{
    // MSNet::RouteIterator myCurrEdge must be a random access iterator.
    if (myCurrEdge + nSuccs >= myRoute->end()) {
        return false;
    }
    else {
        return true;
    }
}

/////////////////////////////////////////////////////////////////////////////

bool
MSVehicle::destReached( const MSEdge* targetEdge )
{
    // search for the target in the vehicle's route. Usually there is
    // only one iteration. Only for very short edges a vehicle can
    // "jump" over one ore more edges in one timestep.
    MSNet::Route::const_iterator edgeIt = myCurrEdge;

    while ( *edgeIt != targetEdge ) {

        ++edgeIt;
        assert( edgeIt != myRoute->end() );
    }

    myCurrEdge = edgeIt;

    // Check if destination-edge is reached. Update allowedLanes makes
    // only sense if destination isn't reached.
    MSNet::Route::const_iterator destination = myRoute->end() - 1;

    if ( myCurrEdge == destination ) {

        return true;
    }
    else {

        myAllowedLanes =
            ( *myCurrEdge )->allowedLanes( **( myCurrEdge + 1 ) );
        return false;
    }
}

/////////////////////////////////////////////////////////////////////////////

double
MSVehicle::brakeGap( const MSLane* lane ) const
{
    // Resolve the vsafe equation to gap. Assume predecessor has
    // speed == 0 and that vsafe will be the current speed plus acceleration,
    // i.e that with this gap there will be no interaction.
    double vNext = vaccel( lane );
    double gap = vNext *
        ( myState.mySpeed * myType->inversTwoDecel() + myTau );

    // If we are very slow, the distance driven with an accelerated speed
    // might be longer.
    double accelDist = myState.mySpeed * MSNet::deltaT() + myType->accelDist();

    // Don't allow timeHeadWay < deltaT situations.
    return max( max( gap, timeHeadWayGap( vNext ) ), accelDist );
}


double
MSVehicle::rigorousBrakeGap(const State &state) const
{
//    double speed = state.mySpeed - myType->decel() * MSNet::deltaT();
    return state.mySpeed *
        ( state.mySpeed * myType->inversTwoDecel() + myTau );
}



/////////////////////////////////////////////////////////////////////////////

double
MSVehicle::interactionGap( const MSLane* lane, const MSVehicle& pred ) const
{
    // Resolve the vsafe equation to gap. Assume predecessor has
    // speed != 0 and that vsafe will be the current speed plus acceleration,
    // i.e that with this gap there will be no interaction.
    double vF = myState.mySpeed;
    double vL = pred.myState.mySpeed;
    double vNext = vaccel( lane );
    double gap = ( vNext - vL  ) *
        ( ( vF + vL ) * myType->inversTwoDecel() + myTau ) +
        vL * myTau;

    // Don't allow timeHeadWay < deltaT situations.
    return max( gap, timeHeadWayGap( vNext ) );
}

/////////////////////////////////////////////////////////////////////////////

bool
MSVehicle::isSafeChange( const MSVehicle& pred, const MSLane* lane ) const
{
    double gap   = gap2pred( pred );
    return hasSafeGap( pred, lane, gap );
}

/////////////////////////////////////////////////////////////////////////////

bool
MSVehicle::hasSafeGap( const MSVehicle& pred,
                       const MSLane* lane,
                       double gap ) const
{
    double vSafe = vsafe( this->speed(), myType->decel(),
                          gap, pred.speed() );
    double vNext = min( vaccel( lane ), vSafe );

//      return ( vNext >= this->speed() - myType->decelSpeed() &&
//               gap   >= timeHeadWayGap( vNext ) );

    return ( vNext >= this->speed() - myType->decelSpeed() &&
             gap   >= timeHeadWayGap( pred.speed() ) );
}



/////////////////////////////////////////////////////////////////////////////

double
MSVehicle::safeEmitGap( void ) const
{
    double vNextMin = max( this->speed() - myType->decelSpeed(),
                           double( 0 ) ); // ok, minimum next speed
    double safeGap  = vNextMin *
        ( this->speed() * myType->inversTwoDecel() + myTau );
    return max( safeGap, timeHeadWayGap( myState.mySpeed ) ) + myType->accelDist();
}


double
MSVehicle::accelDist() const 
{
    return myType->accelDist();
}


/////////////////////////////////////////////////////////////////////////////

double
MSVehicle::vNeighEqualPos( const MSVehicle& neigh )
{
    double v = ( neigh.pos() - this->pos() +
                 neigh.speed() * MSNet::deltaT() ) / MSNet::deltaT();
    assert( v >= 0 );
    // Don't break too hard.
    if ( v < speed() - myType->decel() * MSNet::deltaT() ) {

        return speed() - myType->decelSpeed();
    }

    // Be able to slow down to neighbours speed in following timesteps.
    if ( v >= neigh.speed() + myType->decelSpeed() ) {

        return neigh.speed() + myType->decelSpeed();
    }
    else {

        return v;
    }
}

/////////////////////////////////////////////////////////////////////////////

double
MSVehicle::driveDist( State state ) const
{
    return state.mySpeed * MSNet::deltaT();
}

/////////////////////////////////////////////////////////////////////////////

double
MSVehicle::decelDist() const
{
    return myType->decelDist();
}

/////////////////////////////////////////////////////////////////////////////

MSVehicle::State
MSVehicle::accelState( const MSLane* lane ) const
{
    return State( 0, vaccel( lane ) );
}

/////////////////////////////////////////////////////////////////////////////

void
MSVehicle::move( MSLane* lane,
                 const MSVehicle* pred,
                 const MSVehicle* neigh )
{
#ifdef _SPEEDCHECK
    MSNet::noVehicles++;
#endif
    double vAccel = vaccel( lane );
    double vSafe  = vsafe( myState.mySpeed, myType->decel(),
                           gap2pred( *pred ), pred->speed() );

    double vNext;
    if ( neigh != 0 ) {

        vNext = dawdle( min( vAccel,
                             min( vSafe, vNeighEqualPos( *neigh ) ) ) );
    }
    else {

        vNext = dawdle( min( vAccel, vSafe ) );
    }
    if(vNext<myState.mySpeed-myType->decelSpeed()) {
        vNext = myState.mySpeed-myType->decelSpeed();
    }

    double bla = myState.mySpeed;
    // update position and speed
    myState.myPos  += vNext * MSNet::deltaT();
    assert( myState.myPos < lane->length() );
    myState.mySpeed = vNext;
    assert(bla-this->myType->decel() <= myState.mySpeed);
}


void 
MSVehicle::moveRegardingCritical(MSLane* lane, 
                                 const MSVehicle* pred, 
                                 const MSVehicle* neigh )
{
#ifdef _SPEEDCHECK
    MSNet::noVehicles++;
#endif
    // compute other values as in move
    double vAccel = vaccel( lane );
    double vSafe  = vsafeCritical( pred );

    double vNext;
    if ( neigh != 0 ) {

        vNext = dawdle( min( vAccel,
                             min( vSafe, vNeighEqualPos( *neigh ) ) ) );
    }
    else {

        vNext = dawdle( min( vAccel, vSafe ) );
    }
    if(vNext<myState.mySpeed-myType->decelSpeed()) {
        vNext = myState.mySpeed-myType->decelSpeed();
    }

    double bla = myState.mySpeed;
    // update position and speed
    myState.myPos  += vNext * MSNet::deltaT();
    assert( myState.myPos < lane->length() );
    myState.mySpeed = vNext;
    assert(bla-this->myType->decel() <= myState.mySpeed);
}


void 
 
MSVehicle::_assertPos() const
{
    assert(myState.myPos<myLane->length());
}

double 
MSVehicle::vsafeCritical( const MSVehicle *pred) const
{
    double decelAbility = myType->decel();
    // compute vsafe dependent to the leader
    double minVSafe = vsafe(myState.mySpeed, myType->decel(), 
        gap2pred( *pred ), pred->speed());
    // check whether the vehicle is not on an appropriate lane
    //  decelerate when yes
    if(!myLane->appropriate(this)) {
        return min(minVSafe,
            vsafe(myState.mySpeed, decelAbility, 
                myLane->length() - MSVehicleType::maxLength() - myState.myPos, 0)
                );
    }
    // compute the way the vehicle may drive when accelerating
    double dist = myState.mySpeed * MSNet::deltaT() + myType->accelDist();
    double left = myLane->length() - myState.myPos;
    double drove = left;
    // loop until all the way is checked or vsafe can not get smaller
    //  check junctions and last vehicles on following lanes
    const MSLane *currentLane = myLane;
    while(left>0) {
        double currentVSafe = minVSafe;
        MSLane::LinkCont::const_iterator link = 
            myLane->succLinkSec( *this, 1, *currentLane );
        // the vehicle will have to stop before the next junction
        //  due to a lower priority
        if ( ( (*link)->myPrio == false ) &&
             ( myLane->willLeaveLane( *this ) == false ) ) {
            currentVSafe = vsafe(myState.mySpeed, decelAbility, drove, 0);
            return min(minVSafe, currentVSafe);
        }
        // the vehicle will have to stop due to a traffic light
        if( currentLane->linkClosed(*link) ) {
            currentVSafe = vsafe(myState.mySpeed, decelAbility, drove, 0);
            return min(minVSafe, currentVSafe);
        }
        // check the progress on the following lane
        //  (incrementally from lane to lane)
        currentLane = (*link)->myLane;
        // check whether the next lane is empty; 
        //  if not, check the last vehicle on this lane
        const MSVehicle * const nextPred = currentLane->getLastVehicle();
        if(nextPred!=0) {
            currentVSafe = vsafe(myState.mySpeed, decelAbility, 
                drove, nextPred->speed());
            if(currentVSafe>minVSafe) {
                return minVSafe;
            }
        }
        // check whether vehicle will stop at the next lane
        //  if yes, the currently smallest vsafe can be used
        drove += currentLane->length();
        left -= currentLane->length();
        // when the vehicle ends on the following lane, return
        if(endsOn(*currentLane)) {
            currentVSafe = vsafe(myState.mySpeed, decelAbility, drove, 0);
            minVSafe = min(minVSafe, currentVSafe);
        }
        if(drove>dist) {
            return minVSafe;
        }
    }
    return minVSafe;
}

bool
MSVehicle::endsOn(const MSLane &lane) const
{
    return lane.inEdge((*myRoute)[myRoute->size()-1]);
}

////////////////////////////////////////////////////////////////////////////

void
MSVehicle::moveDecel2laneEnd( MSLane* lane )
{
#ifdef _SPEEDCHECK
    MSNet::noVehicles++;
#endif

    double gap = lane->length() - myState.myPos; // !!!
//!!!    assert( gap <= brakeGap( lane ) );

    // Slow down and dawdle.
    double vSafe  = vsafe( myState.mySpeed, myType->decel(), gap, 0 );
    double vNext  = dawdle( vSafe );
    if(vNext<myState.mySpeed-myType->decelSpeed()) {
        vNext = myState.mySpeed-myType->decelSpeed();
    }

    // update position and speed
    myState.myPos  += vNext * MSNet::deltaT();
//    assert( myState.myPos < lane->length() );
    myState.mySpeed = vNext;
}

////////////////////////////////////////////////////////////////////////////


void
MSVehicle::moveUpdateState( const State newState )
{
#ifdef _SPEEDCHECK
    MSNet::noVehicles++;
#endif

    myState.myPos  += newState.mySpeed * MSNet::deltaT();
    assert( myState.myPos >= 0 );

    myState.mySpeed = newState.mySpeed;
    assert( myState.mySpeed >= 0 );
}

////////////////////////////////////////////////////////////////////////////

void
MSVehicle::moveSetState( const State newState )
{
#ifdef _SPEEDCHECK
    MSNet::noVehicles++;
#endif

    myState = newState;
    assert( myState.myPos >= 0 );
    assert( myState.mySpeed >= 0 );
}

////////////////////////////////////////////////////////////////////////////

MSVehicle::State
MSVehicle::nextState( MSLane* lane,
                      State predState,  double gap2pred,
                      State neighState, double gap2neigh ) const
{
    // Don't move if gap2pred < dontMoveGap to handle arithmetic inaccuracy.
    if ( gap2pred < dontMoveGap ) {

        return State( myState.pos(), 0 );
    }

    // Pragmatic solution: ignore neighbours

    double vAccel   = vaccel( lane );
    double vSafe = 0;
    if ( predState != State() ) {

        assert( gap2pred >= 0 );
        vSafe = vsafe( myState.mySpeed, myType->decel(),
                       gap2pred, predState.mySpeed );
    }
    else {

        vSafe = lane->maxSpeed(); // Don't confuse vMin() with a not set vSafe.
    }

    double vNext   = dawdle( min( vAccel, vSafe ) );
    if(vNext<myState.mySpeed-myType->decelSpeed()) {
        vNext = myState.mySpeed-myType->decelSpeed();
    }
    double nextPos = myState.myPos + vNext * MSNet::deltaT(); // Will be
    // overridden if veh leaves lane.

    return State( nextPos, vNext );
}

/////////////////////////////////////////////////////////////////////////////

MSVehicle::State
MSVehicle::nextState( MSLane* lane, double gap ) const
{
    // Don't move if gap < dontMoveGap to handle arithmetic inaccuracy.
    if ( gap < dontMoveGap ) {

        return State( myState.pos(), 0 );
    }

    // TODO
    // If we know that we will slow down, is there still the need to dawdle?

    double vAccel  = vaccel( lane );
    double vSafe   = vsafe( myState.mySpeed, myType->decel(), gap, 0 );
    double vNext   = dawdle( min( vSafe, vAccel ) );
    if(vNext<myState.mySpeed-myType->decelSpeed()) {
        vNext = myState.mySpeed-myType->decelSpeed();
    }
    double nextPos = myState.myPos + vNext * MSNet::deltaT(); // Will be
    // overridden if veh leaves lane.

    return State( nextPos, vNext );
}

/////////////////////////////////////////////////////////////////////////////

MSVehicle::State
MSVehicle::nextStateCompete( MSLane* lane,
                             State predState,
                             double gap2pred ) const
{
    double vAccel   = vaccel( lane );
    double vSafe    = vsafe( myState.mySpeed, myType->decel(),
                             gap2pred, predState.mySpeed );

    double vNext    = dawdle( min( vAccel, vSafe ) );
    if(vNext<myState.mySpeed-myType->decelSpeed()) {
        vNext = myState.mySpeed-myType->decelSpeed();
    }
    double nextPos  = myState.myPos + vNext * MSNet::deltaT();
    return State( nextPos, vNext );
}

/////////////////////////////////////////////////////////////////////////////

bool
MSVehicle::dictionary(string id, MSVehicle* ptr)
{
    DictType::iterator it = myDict.find(id);
    if (it == myDict.end()) {
        // id not in myDict.
        myDict.insert(DictType::value_type(id, ptr));
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////

MSVehicle*
MSVehicle::dictionary(string id)
{
    DictType::iterator it = myDict.find(id);
    if (it == myDict.end()) {
        // id not in myDict.
        return 0;
    }
    return it->second;
}

/////////////////////////////////////////////////////////////////////////////

void
MSVehicle::clear()
{
    for(DictType::iterator i=myDict.begin(); i!=myDict.end(); i++) {
        delete (*i).second;
    }
    myDict.clear();
}

/////////////////////////////////////////////////////////////////////////////

double
MSVehicle::speed() const
{
    return myState.mySpeed;
}

/////////////////////////////////////////////////////////////////////////////

bool
MSVehicle::laneChangeBrake2much( const State brakeState )
{
    // SK-vnext can reduce speed about decel, dawdle about accel.
    double minAllowedNextSpeed =
        max( myState.mySpeed - myType->accelPlusDecelSpeed(),
             static_cast< double >( 0 ) );

    if ( brakeState.mySpeed < minAllowedNextSpeed ) {

        return true;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////

string
MSVehicle::id() const
{
    return myID;
}

/////////////////////////////////////////////////////////////////////////////

ostream&
operator<<( ostream& os, const MSVehicle& veh )
{
    os << "MSVehicle: Id = " << veh.myID << endl;
    return os;
}

/////////////////////////////////////////////////////////////////////////////

MSVehicle::XMLOut::XMLOut( const MSVehicle& obj,
                           unsigned indentWidth,
                           bool withChildElemes ) :
    myObj( obj ),
    myIndentWidth( indentWidth ),
    myWithChildElemes( withChildElemes )
{
}

/////////////////////////////////////////////////////////////////////////////

ostream&
operator<<( ostream& os, const MSVehicle::XMLOut& obj )
{
    string indent( obj.myIndentWidth , ' ' );

    os << indent << "<vehicle id=\"" << obj.myObj.myID << "\" pos=\""
       << obj.myObj.pos() << "\" speed=\"" << obj.myObj.speed()
       << "\"/>" << endl;

// Currently there are no child elements. Maybe persons will be in future.
//    if ( obj.myWithChildElemes ) {
//
//    }

    return os;
}

/////////////////////////////////////////////////////////////////////////////

double
MSVehicle::vaccel( const MSLane* lane ) const
{
    // Accelerate until vehicle's max speed reached.
    double vVehicle = min( myState.mySpeed + myType->accelSpeed(),
                           myType->myMaxSpeed );

    // But don't drive faster than max lane speed.
    return min( vVehicle, lane->maxSpeed() );
}

/////////////////////////////////////////////////////////////////////////////

bool
MSVehicle::onAllowed( const MSLane* lane ) const
{
     MSEdge::LaneCont::const_iterator compare =
        find( myAllowedLanes->begin(), myAllowedLanes->end(), lane );
     return ( compare != myAllowedLanes->end() );
}

/////////////////////////////////////////////////////////////////////////////

bool
MSVehicle::isInsertTimeHeadWayCond( double predSpeed, double gap2pred )
{
    return gap2pred >= timeHeadWayGap( predSpeed );
}

/////////////////////////////////////////////////////////////////////////////

bool
MSVehicle::isInsertTimeHeadWayCond( MSVehicle& aPred )
{
    return gap2pred( aPred ) >= timeHeadWayGap( aPred.speed() );
}

/////////////////////////////////////////////////////////////////////////////

bool
MSVehicle::isInsertBrakeCond( double predSpeed, double gap2pred )
{
    return vsafe( speed(), myType->decel(), gap2pred, predSpeed )
        >= speed() - myType->decelSpeed();
}

/////////////////////////////////////////////////////////////////////////////

bool
MSVehicle::isInsertBrakeCond( MSVehicle& aPred )
{
    return vsafe( speed(), myType->decel(), gap2pred( aPred ), aPred.speed() )
        >= speed() - myType->decelSpeed();
}

/////////////////////////////////////////////////////////////////////////////

void
MSVehicle::dumpData( unsigned index )
{
    MeanDataValues& md = myMeanData[ index ];
    
    double leaveTimestep =
        static_cast< double >( MSNet::getInstance()->timestep() );
    
    myLane->addVehicleData( leaveTimestep - md.entryContTimestep,
                            MSNet::getInstance()->timestep() -
                            md.entryDiscreteTimestep,
                            myState.myPos - md.entryPos,
                            md.speedSum,
                            md.speedSquareSum,
                            index,
                            false );

    resetMeanData( index );
}
/////////////////////////////////////////////////////////////////////////////

void
MSVehicle::resetMeanData( unsigned index )
{
    MeanDataValues& md = myMeanData[ index ];

    MSNet::Time timestep = MSNet::getInstance()->timestep();
    
    md.entryContTimestep     = static_cast< double >( timestep );
    md.entryDiscreteTimestep = timestep;
    md.entryPos              = myState.myPos;
    md.speedSum              = 0;
    md.speedSquareSum        = 0;
}

/////////////////////////////////////////////////////////////////////////////

void
MSVehicle::updateMeanData( double entryTimestep,
                           double pos,
                           double speed )
{
    double speedSquare = speed * speed;
    unsigned discreteTimestep = MSNet::getInstance()->timestep();
    
    for ( vector< MeanDataValues >::iterator md = myMeanData.begin();
          md != myMeanData.end(); ++md ) {
        
        md->entryContTimestep  = entryTimestep;
        md->entryDiscreteTimestep = discreteTimestep;
        md->entryPos       = pos;
        md->speedSum       = speed;
        md->speedSquareSum = speedSquare;
    }
}


/////////////////////////////////////////////////////////////////////////////

void
MSVehicle::enterLaneAtMove( MSLane* enteredLane )
{
    myLane = enteredLane;
    double entryTimestep =
        static_cast< double >( MSNet::getInstance()->timestep() ) -
        myState.myPos / myState.mySpeed;
    updateMeanData( entryTimestep, 0, myState.mySpeed );
}

/////////////////////////////////////////////////////////////////////////////

void
MSVehicle::enterLaneAtLaneChange( MSLane* enteredLane )
{
    myLane = enteredLane;
    updateMeanData( static_cast< double >( MSNet::getInstance()->timestep() ),
                    myState.myPos, myState.mySpeed );
}

/////////////////////////////////////////////////////////////////////////////

void
MSVehicle::enterLaneAtEmit( MSLane* enteredLane )
{
    myLane = enteredLane;
    updateMeanData( static_cast< double >( MSNet::getInstance()->timestep() ),
                    myState.myPos, myState.mySpeed );
}

/////////////////////////////////////////////////////////////////////////////

void
MSVehicle::leaveLaneAtMove( void )
{
    double leaveTimestep =
        static_cast< double >( MSNet::getInstance()->timestep() ) - 1 +
        ( MSNet::deltaT() - myState.myPos / myState.mySpeed );
    
    for ( unsigned index = 0; index < myMeanData.size(); ++index ) {

        MeanDataValues& md = myMeanData[ index ];

//          // LeaveTimestep shouldn't contribute to meanSpeed. At measure
//          // time the vehicle isn't any longer on current myLane.
//          double speedSum = md.speedSum - myState.mySpeed;
//          double speedSquareSum =  md.speedSquareSum -
//              myState.mySpeed * myState.mySpeed;
//          if ( speedSum < 0 ) {
//              speedSum = 0;
//              speedSquareSum = 0;
//          }
        
        myLane->addVehicleData( leaveTimestep - md.entryContTimestep,
                                MSNet::getInstance()->timestep() -
                                md.entryDiscreteTimestep - 1,
                                myLane->length() - md.entryPos,
                                md.speedSum,
                                md.speedSquareSum,
                                index,
                                true );
    }
}

/////////////////////////////////////////////////////////////////////////////

void
MSVehicle::leaveLaneAtLaneChange( void )
{
    double leaveTimestep =
        static_cast< double >( MSNet::getInstance()->timestep() );
    
    for ( unsigned index = 0; index < myMeanData.size(); ++index ) {

        MeanDataValues& md = myMeanData[ index ];

//          // LeaveTimestep shouldn't contribute to meanSpeed. At measure
//          // time the vehicle isn't any longer on current myLane.
//          double speedSum = md.speedSum - myState.mySpeed;
//          double speedSquareSum =  md.speedSquareSum -
//              myState.mySpeed * myState.mySpeed;
//          if ( speedSum < 0 ) {
//              speedSum = 0;
//              speedSquareSum = 0;
//          }
        
        myLane->addVehicleData( leaveTimestep - md.entryContTimestep,
                                MSNet::getInstance()->timestep() -
                                md.entryDiscreteTimestep - 1,
                                myState.myPos - md.entryPos,
                                md.speedSum,
                                md.speedSquareSum,
                                index,
                                false );
    }
}

/////////////////////////////////////////////////////////////////////////////

void
MSVehicle::meanDataMove( void )
{
    double speed = myState.mySpeed;
    double speedSquare = speed * speed;
    
    for ( vector< MeanDataValues >::iterator md = myMeanData.begin();
          md != myMeanData.end(); ++md ) {
        
        md->speedSum       += speed;
        md->speedSquareSum += speedSquare;
    }
}



/////////////////////////////////////////////////////////////////////////////

const MSEdge * const
MSVehicle::getEdge() const
{
    return *myCurrEdge;
}



bool 
MSVehicle::reachingCritical(double laneLength) const
{
    // check whether the vehicle will run over the lane when accelerating
    return (laneLength 
        - myState.myPos - brakeGap(myLane)) <= 0;
}


double 
MSVehicle::decelAbility() const
{
    return myType->decel() * MSNet::deltaT();
}


/**************** DO NOT DEFINE ANYTHING AFTER THE INCLUDE *****************/

#ifdef DISABLE_INLINE
#include "MSVehicle.icc"
#endif

// Local Variables:
// mode:C++
// End:

