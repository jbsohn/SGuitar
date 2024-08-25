//
//  main.m
//  SGuitar
//
//  Created by John on 8/20/24.
//

@import Foundation;
#include "SGChord.h"
#include "SGNoteValue.h"
#include "SGGuitar.h"

int main(int argc, const char * argv[]) {
    SGChord *chord = [SGChord createWithRootNoteValue:SGNoteValueC intervals:@[@0, @4, @7]];
    NSLog(@"chord: %@", [chord getDescription]);
    
    SGGuitar *guitar = [SGGuitar create];
    [guitar getAdjustment:@""];
}
