#ifndef help_h
#define help_h
/***************************************************************************
                          help.h
              the help text
                             -------------------
    project              : OD2TRIPS
    begin                : 11.09.2002
    copyright            : (C) 2002 by DLR/IVF http://ivf.dlr.de/
    author               : Peter Mieth
    email                : Peter.Mieth@dlr.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// $Log$
// Revision 1.9  2004/12/20 14:05:16  dkrajzew
// version patched
//
/* =========================================================================
 * included modules
 * ======================================================================= */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H


/* =========================================================================
 * definitions
 * ======================================================================= */
/**
 * The list of help strings for the sumo-od2trips module
 */
char *help[] = {
    "Simulation of Urban MObility v0.8.2.1 - od2trips application",
    "  Merges OD matrix and net to trip tables.",
    "  http://sumo.sourceforge.net",
    "Usage: od2trips [OPTION]*",
    " ",
    "Examples: ",
    " od2trips -n ./MD_Netz.net.xml -d ./muenchen1.inp -o ./triptable.txt -vC",
    " od2trips -c od2trips.cfg",
    " ",
    "Options:",
    " Input files and pathes:",
    "   -c, --configuration-file FILE  FILE will be used as configuration",
    "   -n, --net-file FILE            Net definitions in XML-format",
    "   -d, --od-file FILE             Meta file (VISSIM) *.inp",
    "   -i, --od-path PATH             Path to OD input files *.fma",
    " ",
    " Output files:",
    "   -o, --output-file FILE         The generated trip table will be written"
    "                                   to FILE",
    " ",
    " Processing Options:",
    "   -b, --begin INT                Time to begin with (in s)",
    "   -e, --end INT                  Time to end with (in s)",
    "   -s, --scale FLOAT              Norming factor",
    "                                   The number of trips is =",
    "                                           number of read/factor",
    "   --no-color                     Suppresses color saving.",
    "   --srand INT                    Initialises the random number generator",
    "                                   with the given value",
    "   --abs-rand                     Set this when the current time shall be",
    "                                   used for random number initialisation",
    " Report options:",
    "   -v, --verbose                  SUMO-OD2TRIPS will report what it does",
    "   -W, --suppress-warnings        No warnings will be printed",
    "   -l, --log-file FILE            Writes all messages to the file",
    "   -p, --print-options            Prints option values before processing",
    "   -?, --help                     This screen",
    0
};

#endif
