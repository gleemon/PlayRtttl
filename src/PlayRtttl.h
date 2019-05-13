/*
 * PlayRtttl.h
 *
 * Includes 21 sample melodies.
 * The example melodies may have copyrights you have to respect.
 * More RTTTL songs can be found under http://www.picaxe.com/RTTTL-Ringtones-for-Tune-Command/
 *
 *  Copyright (C) 2018  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *     Based on the RTTTL.pde example code written by Brett Hagman
 *     http://www.roguerobotics.com/
 *     bhagman@roguerobotics.com
 *
 *
 *  This file is part of PlayRttl https://github.com/ArminJo/PlayRttl.
 *
 *  PlayRttl is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/gpl.html>.
 *
 */

#ifndef SRC_PLAYRTTTL_H_
#define SRC_PLAYRTTTL_H_

#include <avr/pgmspace.h>
#include "pitches.h"

#define VERSION_SERVO_EASING 1.2.0
/*
 * Version 1.1
 * - new setNumberOfLoops() and setDefaultStyle() functions.
 */


#define SUPPORT_EXTENSIONS // needs 200 bytes FLASH
#define SUPPORT_RTX_FORMAT // needs 100 bytes FLASH

#ifdef SUPPORT_RTX_FORMAT
#define SUPPORT_EXTENSIONS
#endif

#define DEFAULT_DURATION 4
#define DEFAULT_OCTAVE 6
#define DEFAULT_BPM 63

#define RTX_STYLE_CONTINUOUS 'C'  // Tone length = note length
#define RTX_STYLE_NATURAL 'N'     // Tone length = note length - 1/16
#define RTX_STYLE_STACCATO 'S'    // Tone length = note length - 1/2
#define RTTTL_STYLE_CONTINUOUS 0  // Tone length = note length
#define RTTTL_STYLE_NATURAL 16     // Tone length = note length - 1/16
#define RTTTL_STYLE_STACCATO 2    // Tone length = note length - 1/2
#define RTTTL_STYLE_4 4           // Tone length = note length - 1/4
#define RTTTL_STYLE_8 8           // Tone length = note length - 1/8
#define DEFAULT_STYLE RTTTL_STYLE_CONTINUOUS

void setTonePinIsInverted(bool aTonePinIsInverted);

#ifdef SUPPORT_EXTENSIONS
void setNumberOfLoops(uint8_t aNumberOfLoops);
void setDefaultStyle(uint8_t aDefaultStyleDivisorValue);
uint8_t convertStyleCharacterToDivisorValue(char aStyleCharacter);
#endif

void startPlayRtttl(uint8_t aTonePin, char *aRTTTLArrayPtr, void (*aOnComplete)()=NULL);
void playRtttlBlocking(uint8_t aTonePin, char *aRTTTLArrayPtr);

void startPlayRtttlPGM(uint8_t aTonePin, const char *aRTTTLArrayPtrPGM, void (*aOnComplete)()=NULL);
void playRtttlBlockingPGM(uint8_t aTonePin, const char *aRTTTLArrayPtrPGM);

void startPlayRandomRtttlFromArrayPGM(uint8_t aTonePin, const char* const aSongArrayPGM[], uint8_t aNumberOfEntriesInSongArrayPGM,
        char* aBufferPointer = NULL, uint8_t aBufferPointerSize = 0, void (*aOnComplete)()=NULL);
void playRandomRtttlBlocking(uint8_t aTonePin);

// To be called from loop. - Returns true if tone is playing, false if tone has ended or stopped
bool updatePlayRtttl(void);

void stopPlayRtttl(void);

void getRtttlNamePGM(const char *aRTTTLArrayPtrPGM, char * aBuffer, uint8_t aBuffersize);
void getRtttlName(char *aRTTTLArrayPtr, char * aBuffer, uint8_t aBuffersize);

void printNamePGM(const char *aRTTTLArrayPtrPGM);

struct playRtttlState {
    long MillisOfNextAction;
    const char * NextTonePointer;

    struct {
        uint8_t IsStopped :1;
        uint8_t IsPGMMemory :1;
        uint8_t IsTonePinInverted :1; // True if tone pin has inverted logic i.e. is active on low.
    } Flags;

    // Tone pin to use for output
    uint8_t TonePin;
    // Callback on completion of tone
    void (*OnComplete)(void);

    uint8_t DefaultDuration;
    uint8_t DefaultOctave;
    long TimeForWholeNoteMillis;
#ifdef SUPPORT_EXTENSIONS
    const char * LastTonePointer; // used for loops
    // The divisor for the formula: Tone length = note length - note length * (1 / divisor)
    // If 0 then Tone length = note length;
    uint8_t StyleDivisorValue;
    uint8_t NumberOfLoops;  // 0 means forever, 1 means we are in the last loop
#endif
};

/*
 * RTTTL format:
 *  opt duration
 *  note
 *  opt dot to increase duration by half
 *  opt octave
 */
/*
 * Disclaimer: These ringtone melodies are for personal enjoyment only. All copyright belongs to its respective author.
 */
static const char StarWars[] PROGMEM = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
static const char MahnaMahna[] PROGMEM = "MahnaMahna:d=16,o=6,b=125:c#,c.,b5,8a#.5,8f.,4g#,a#,g.,4d#,8p,c#,c.,b5,8a#.5,8f.,g#.,8a#.,4g,8p,c#,c.,b5,8a#.5,8f.,4g#,f,g.,8d#.,f,g.,8d#.,f,8g,8d#.,f,8g,d#,8c,a#5,8d#.,8d#.,4d#,8d#.";
static const char MissionImp[] PROGMEM = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
static const char Entertainer[] PROGMEM = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
static const char Muppets[] PROGMEM = "Muppets:d=4,o=5,b=250:c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,8a,8p,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,8e,8p,8e,g,2p,c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,a,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,d,8d,c";
static const char Flinstones[] PROGMEM = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6,16f6,16a#.,16a#6,32g6,16f6,16a#.,32f6,32f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,a#,16a6,16d.6,16a#6,32a6,32a6,32g6,32f#6,32a6,8g6,16g6,16c.6,32a6,32a6,32g6,32g6,32f6,32e6,32g6,8f6,16f6,16a#.,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#6,16c7,8a#.6";
static const char YMCA[] PROGMEM = "YMCA:d=4,o=5,b=160:8c#6,8a#,2p,8a#,8g#,8f#,8g#,8a#,c#6,8a#,c#6,8d#6,8a#,2p,8a#,8g#,8f#,8g#,8a#,c#6,8a#,c#6,8d#6,8b,2p,8b,8a#,8g#,8a#,8b,d#6,8f#6,d#6,f.6,d#.6,c#.6,b.,a#,g#";
static const char Simpsons[] PROGMEM = "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
static const char Indiana[] PROGMEM = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
static const char Looney[] PROGMEM = "Looney:d=4,o=5,b=140:32p,c6,8f6,8e6,8d6,8c6,a.,8c6,8f6,8e6,8d6,8d#6,e.6,8e6,8e6,8c6,8d6,8c6,8e6,8c6,8d6,8a,8c6,8g,8a#,8a,8f";
static const char Bond[] PROGMEM = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
static const char GoodBad[] PROGMEM = "GoodBad:d=4,o=5,b=56:32p,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,d#,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,c#6,32a#,32d#6,32a#,32d#6,8a#.,16f#.,32f.,32d#.,c#,32a#,32d#6,32a#,32d#6,8a#.,16g#.,d#";
static const char PinkPanther[] PROGMEM = "PinkPanther:d=4,o=5,b=160:8d#,8e,2p,8f#,8g,2p,8d#,8e,16p,8f#,8g,16p,8c6,8b,16p,8d#,8e,16p,8b,2a#,2p,16a,16g,16e,16d,2e";
static const char A_Team[] PROGMEM = "A-Team:d=8,o=5,b=125:4d#6,a#,2d#6,16p,g#,4a#,4d#.,p,16g,16a#,d#6,a#,f6,2d#6,16p,c#.6,16c6,16a#,g#.,2a#";
static const char Jeopardy[] PROGMEM = "Jeopardy:d=4,o=6,b=125:c,f,c,f5,c,f,2c,c,f,c,f,a.,8g,8f,8e,8d,8c#,c,f,c,f5,c,f,2c,f.,8d,c,a#5,a5,g5,f5,p,d#,g#,d#,g#5,d#,g#,2d#,d#,g#,d#,g#,c.7,8a#,8g#,8g,8f,8e,d#,g#,d#,g#5,d#,g#,2d#,g#.,8f,d#,c#,c,p,a#5,p,g#.5,d#,g#";
static const char Gadget[] PROGMEM = "Gadget:d=16,o=5,b=50:32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,32d#,32f,32f#,32g#,a#,d#6,4d6,32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,8d#";
static const char Smurfs[] PROGMEM = "Smurfs:d=32,o=5,b=200:4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8f#,p,8a#,p,4g#,4p,g#,p,a#,p,b,p,c6,p,4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8b,p,8f,p,4f#";
static const char Toccata[] PROGMEM ="Toccata:d=4,o=5,b=160:16a,16g,1a,16g,16f,16d,16e,2c#,16p,d.,8p,p,2p,16a,16g,1a,8e.,8f.,8c#.,2d";
static const char STrek[] PROGMEM ="Star Trek:d=4,o=5,b=63:8f.,16a#,d#.6,8d6,16a#.,16g.,16c.6,f6";
static const char Scooby[] PROGMEM = "ScoobyDoo:d=4,o=5,b=160:8e6,8e6,8d6,8d6,2c6,8d6,e6,2a,8a,b,g,e6,8d6,c6,8d6,2e6,p,8e6,8e6,8d6,8d6,2c6,8d6,f6,2a,8a,b,g,e6,8d6,2c6";
static const char Scooby2[] PROGMEM = "ScoobyDo:d=4,o=5,b=160:8e6,8e6,8d6,8d6,2c6,8d6,e6,2a,16p,8a,b,g,e6,8e6,d6,c6,2p,8e6,8e6,8d6,8d6,2c6,8d6,e6,2f6,8a,g,g,e6,8e6,8d6,8d6,c6,2p,8e6,8e6,8d6,8d6,2c6,8d6,f6,a,8p,8a,8b,8b,g,e6,8e6,d6,e6,2p,8e6,8e6,8d6,8d6,c6,8p,8c6,8d6,e6,2f6,8a,g,g,e6,8e6,d6,c6,8p,8c6,8d6,8e6,8f6,8e6,8f6,8e6,8f6,8e6,8f6,8e6,16f6,16e6,f6,8e6,16f6,16f6,8f6,16f6,8f6,e6,p,8p,8g6,16g6,8g6,e6,p,8p";
static const char Monty[]="MontyP:d=4,o=5,b=200:f6,8e6,d6,8c#6,c6,8b,a#,8a,8g,8a,8a#,a,8g,2c6,8p,8c6,8a,8p,8a,8a,8g#,8a,8f6,8p,8c6,8c6,8p,8a,8a#,8p,8a#,8a#,8p,8c6,2d6,8p,8a#,8g,8p,8g,8g,8f#,8g,8e6,8p,8d6,8d6,8p,8a#,8a,8p,8a,8a,8p,8a#,2c6,8p,8c6";
static const char DrWho[] PROGMEM ="DrWho:d=4,o=6,b=80:b.5,8g5,16b.5,8a.5,32g.5,32f#5,g.5,e,32d,32c,8d,8g5,8e.,32d,32c,8d,8b5,2a5,32g5,32f#5,2g5";
static const char Aadams[] PROGMEM = "aadams:d=4,o=5,b=160:8c,f,8a,f,8c,b4,2g,8f,e,8g,e,8e4,a4,2f,8c,f,8a,f,8c,b4,2g,8f,e,8c,d,8e,1f,8c,8d,8e,8f,1p,8d,8e,8f#,8g,1p,8d,8e,8f#,8g,p,8d,8e,8f#,8g,p,8c,8d,8e,8f";
static const char Cantina[] PROGMEM = "Cantina:d=4,o=5,b=250:8a,8p,8d6,8p,8a,8p,8d6,8p,8a,8d6,8p,8a,8p,8g#,a,8a,8g#,8a,g,8f#,8g,8f#,f.,8d.,16p,p.,8a,8p,8d6,8p,8a,8p,8d6,8p,8a,8d6,8p,8a,8p,8g#,8a,8p,8g,8p,g.,8f#,8g,8p,8c6,a#,a,g";
static const char Trek[] PROGMEM = "Trek:d=4,o=6,b=225:2b.4,4e.5,1a5,4g#.5,4e.5,4c#.5,4f#.5,2b.5,4b.5,2d#.6";
static const char ImpMarch[] PROGMEM = "SW-ImpMrch:d=4,o=5,b=112:8d.,16p,8d.,16p,8d.,16p,8a#4,16p,16f,8d.,16p,8a#4,16p,16f,d.,8p,8a.,16p,8a.,16p,8a.,16p,8a#,16p,16f,8c#.,16p,8a#4,16p,16f,d.,8p,8d.6,16p,8d,16p,16d,8d6,8p,8c#6,16p,16c6,16b,16a#,8b,8p,16d#,16p,8g#,8p,8g,16p,16f#,16f,16e,8f,8p,16a#4,16p,8c#,8p,8a#4,16p,16c#,8f.,16p,8d,16p,16f,a.,8p,8d.6,16p,8d,16p,16d,8d6,8p,8c#6,16p,16c6,16b,16a#,8b,8p,16d#,16p,8g#,8p,8g,16p,16f#,16f,16e,8f,8p,16a#4,16p,8c#";
static const char Arabian[] PROGMEM = "ArabianN:d=16,o=6,b=63:8a#5,a#.5,c.,c#,4f.,32e,32f,8e,c#,c,c#.,c.,a#5,4f.,c#,c#.,c.,a#5,8f.,f,g#.,f.,d#,8f.,32c#,32f,e.,c#.,e,2f";
static const char Mario[] PROGMEM = "SuperMar:d=16,o=6,b=112:e,32p,8e,c,8e,8g,8g5,8c,p,8g5,p,8e5,p,8a5,8b5,a#5,8a5,g.5,e,g,8a,f,8g,8e,c,d,8b5,p,8c,p,8g5,p,8e5,p,8a5,8b5,a#5,8a5,g.5,e,g,8a,f,8g,8e";
static const char Future[] PROGMEM = "BackToTh:d=4,o=5,b=160:p,8c.,16p,g,16p,16c.6,16p,a#.,16p,16a,16p,16g,16p,8a,16p,8g,16p,8f,16p,1g.,1p,g.,16p,c.,16p,2f#.,16p,32g.,32p,32a.,32p,8g,32p,8e,32p,8c,32p,f#,16p,32g.,32p,32a.,32p,8g.,32p,8d.,32p,8g.,32p,8d.6,32p,d6,16p,c#6,16p,32b.,32p,32c#.6,32p,2d6";
static const char Potter[] PROGMEM = "HarryPot:d=8,o=6,b=100:b5,e.,16g,f#,4e,b,4a.,4f#.,e.,16g,f#,4d,f,2b5,p,b5,e.,16g,f#,4e,b,4d7,c#7,4c7,g#,c.7,16b,a#,4a#5,g,2e";
static const char Hawaii50[] PROGMEM = "Hawaii50:d=8,o=6,b=180:g5,g5,a#5,4d,2c,1g5,g5,g5,f5,4a#5,1g.5,g5,g5,a#5,4d,2c,1g,f,f,d,4a#5,1g,4a#,g,f,d#,c,d#,f,d#,1c,4c7,a,g,f,d,c,a#5,c,4d,c,4a#5,4c.,2g.,f,f,d,4a#5,2c";
static const char STComm1[] PROGMEM = "StarTrek:d=32,o=7,b=180:d#,e,g,d#,g,d#,f#,e,f,2p,d#,e,g,d#,g,d#,f#,e,f,2p,d#,e,g,d#,g,d#,f#,e,f";
static const char STComm2[] PROGMEM = "StarTrek:d=32,o=6,b=225:16c#,d,d#,4e.,d#,d,8c#";
static const char Mermaid[] PROGMEM = "TheLittl:d=4,o=5,b=200:8d,8f,8a#,d6,d6,8a#,c6,d#6,d6,a#,8a#4,8d,8f,a#,a#,8c,a,c6,a#,p,8d,8f,8a#,d6,d6,8a#,c6,d#6,d6,a#,8a#4,8d,8f,a#,a#,8c,a,c6,16a#,16d,16a#,16d,16a#,16d,16a#tarTrek:d=32,o=6,b=225:16c#,d,d#,4e.,d#,d,8c#";

/*
 * Array of songs. Useful for random melody
 */
#pragma GCC diagnostic ignored "-Wunused-variable"
static const char * const RTTTLMelodies[] PROGMEM = { StarWars, MahnaMahna, MissionImp, Flinstones, YMCA, Simpsons, Indiana, Entertainer, Muppets, Looney, Bond, StarWars, GoodBad, PinkPanther, A_Team, Jeopardy, Gadget, Smurfs, Toccata,
	Scooby, Scooby2, Monty, DrWho, Aadams, Cantina, Trek, ImpMarch, Arabian, Mario, Future, Potter, Hawaii50, STComm1, STComm2, Mermaid };
#define ARRAY_SIZE_MELODIES (sizeof(RTTTLMelodies)/sizeof(const char *))




extern struct playRtttlState sPlayRtttlState;
#ifdef SUPPORT_EXTENSIONS
extern uint8_t sDefaultStyleDivisorValue;
#endif

#endif /* SRC_PLAYRTTTL_H_ */
