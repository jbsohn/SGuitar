//
//  SGuitarTests.m
//  SGuitarTests
//
//  Created by John on 8/25/24.
//

#import <XCTest/XCTest.h>
#import "SGScale.h"
#import "SGChord.h"

@interface SGuitarTests : XCTestCase

@end

@implementation SGuitarTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testExample {
    SGChord *chord = [SGChord createWithRootNoteValue:SGNoteValueC intervals:@[@0, @4, @7]];
    NSLog(@"chord: %@", [chord getDescription]);
    XCTAssertTrue([[chord getDescription] isEqualToString:@"C E G "]);
    
    SGScale *scale = [SGScale createWithRootNoteValue:SGNoteValueC semitones:@[@2, @2, @1, @2, @2, @2]];
    NSLog(@"scale: %@", [scale getDescription]);
    XCTAssertTrue([[scale getDescription] isEqualToString:@"C D E F G A B "]);
}

@end
