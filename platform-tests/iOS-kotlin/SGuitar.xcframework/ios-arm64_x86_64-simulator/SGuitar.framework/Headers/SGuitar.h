#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSError.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSString.h>
#import <Foundation/NSValue.h>

@class SGuitarNoteValue, SGuitarKotlinEnumCompanion, SGuitarKotlinEnum<E>, SGuitarNoteValueCompanion, SGuitarKotlinArray<T>;

@protocol SGuitarKotlinComparable, SGuitarKotlinIterator;

NS_ASSUME_NONNULL_BEGIN
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-warning-option"
#pragma clang diagnostic ignored "-Wincompatible-property-type"
#pragma clang diagnostic ignored "-Wnullability"

#pragma push_macro("_Nullable_result")
#if !__has_feature(nullability_nullable_result)
#undef _Nullable_result
#define _Nullable_result _Nullable
#endif

__attribute__((swift_name("KotlinBase")))
@interface SGuitarBase : NSObject
- (instancetype)init __attribute__((unavailable));
+ (instancetype)new __attribute__((unavailable));
+ (void)initialize __attribute__((objc_requires_super));
@end

@interface SGuitarBase (SGuitarBaseCopying) <NSCopying>
@end

__attribute__((swift_name("KotlinMutableSet")))
@interface SGuitarMutableSet<ObjectType> : NSMutableSet<ObjectType>
@end

__attribute__((swift_name("KotlinMutableDictionary")))
@interface SGuitarMutableDictionary<KeyType, ObjectType> : NSMutableDictionary<KeyType, ObjectType>
@end

@interface NSError (NSErrorSGuitarKotlinException)
@property (readonly) id _Nullable kotlinException;
@end

__attribute__((swift_name("KotlinNumber")))
@interface SGuitarNumber : NSNumber
- (instancetype)initWithChar:(char)value __attribute__((unavailable));
- (instancetype)initWithUnsignedChar:(unsigned char)value __attribute__((unavailable));
- (instancetype)initWithShort:(short)value __attribute__((unavailable));
- (instancetype)initWithUnsignedShort:(unsigned short)value __attribute__((unavailable));
- (instancetype)initWithInt:(int)value __attribute__((unavailable));
- (instancetype)initWithUnsignedInt:(unsigned int)value __attribute__((unavailable));
- (instancetype)initWithLong:(long)value __attribute__((unavailable));
- (instancetype)initWithUnsignedLong:(unsigned long)value __attribute__((unavailable));
- (instancetype)initWithLongLong:(long long)value __attribute__((unavailable));
- (instancetype)initWithUnsignedLongLong:(unsigned long long)value __attribute__((unavailable));
- (instancetype)initWithFloat:(float)value __attribute__((unavailable));
- (instancetype)initWithDouble:(double)value __attribute__((unavailable));
- (instancetype)initWithBool:(BOOL)value __attribute__((unavailable));
- (instancetype)initWithInteger:(NSInteger)value __attribute__((unavailable));
- (instancetype)initWithUnsignedInteger:(NSUInteger)value __attribute__((unavailable));
+ (instancetype)numberWithChar:(char)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedChar:(unsigned char)value __attribute__((unavailable));
+ (instancetype)numberWithShort:(short)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedShort:(unsigned short)value __attribute__((unavailable));
+ (instancetype)numberWithInt:(int)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedInt:(unsigned int)value __attribute__((unavailable));
+ (instancetype)numberWithLong:(long)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedLong:(unsigned long)value __attribute__((unavailable));
+ (instancetype)numberWithLongLong:(long long)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedLongLong:(unsigned long long)value __attribute__((unavailable));
+ (instancetype)numberWithFloat:(float)value __attribute__((unavailable));
+ (instancetype)numberWithDouble:(double)value __attribute__((unavailable));
+ (instancetype)numberWithBool:(BOOL)value __attribute__((unavailable));
+ (instancetype)numberWithInteger:(NSInteger)value __attribute__((unavailable));
+ (instancetype)numberWithUnsignedInteger:(NSUInteger)value __attribute__((unavailable));
@end

__attribute__((swift_name("KotlinByte")))
@interface SGuitarByte : SGuitarNumber
- (instancetype)initWithChar:(char)value;
+ (instancetype)numberWithChar:(char)value;
@end

__attribute__((swift_name("KotlinUByte")))
@interface SGuitarUByte : SGuitarNumber
- (instancetype)initWithUnsignedChar:(unsigned char)value;
+ (instancetype)numberWithUnsignedChar:(unsigned char)value;
@end

__attribute__((swift_name("KotlinShort")))
@interface SGuitarShort : SGuitarNumber
- (instancetype)initWithShort:(short)value;
+ (instancetype)numberWithShort:(short)value;
@end

__attribute__((swift_name("KotlinUShort")))
@interface SGuitarUShort : SGuitarNumber
- (instancetype)initWithUnsignedShort:(unsigned short)value;
+ (instancetype)numberWithUnsignedShort:(unsigned short)value;
@end

__attribute__((swift_name("KotlinInt")))
@interface SGuitarInt : SGuitarNumber
- (instancetype)initWithInt:(int)value;
+ (instancetype)numberWithInt:(int)value;
@end

__attribute__((swift_name("KotlinUInt")))
@interface SGuitarUInt : SGuitarNumber
- (instancetype)initWithUnsignedInt:(unsigned int)value;
+ (instancetype)numberWithUnsignedInt:(unsigned int)value;
@end

__attribute__((swift_name("KotlinLong")))
@interface SGuitarLong : SGuitarNumber
- (instancetype)initWithLongLong:(long long)value;
+ (instancetype)numberWithLongLong:(long long)value;
@end

__attribute__((swift_name("KotlinULong")))
@interface SGuitarULong : SGuitarNumber
- (instancetype)initWithUnsignedLongLong:(unsigned long long)value;
+ (instancetype)numberWithUnsignedLongLong:(unsigned long long)value;
@end

__attribute__((swift_name("KotlinFloat")))
@interface SGuitarFloat : SGuitarNumber
- (instancetype)initWithFloat:(float)value;
+ (instancetype)numberWithFloat:(float)value;
@end

__attribute__((swift_name("KotlinDouble")))
@interface SGuitarDouble : SGuitarNumber
- (instancetype)initWithDouble:(double)value;
+ (instancetype)numberWithDouble:(double)value;
@end

__attribute__((swift_name("KotlinBoolean")))
@interface SGuitarBoolean : SGuitarNumber
- (instancetype)initWithBool:(BOOL)value;
+ (instancetype)numberWithBool:(BOOL)value;
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Note")))
@interface SGuitarNote : SGuitarBase
- (instancetype)initWithMidiNote:(int32_t)midiNote __attribute__((swift_name("init(midiNote:)"))) __attribute__((objc_designated_initializer));
- (instancetype)initWithNote:(SGuitarNoteValue *)note octave:(int32_t)octave __attribute__((swift_name("init(note:octave:)"))) __attribute__((objc_designated_initializer));
- (NSString *)description_ __attribute__((swift_name("description_()")));
- (int32_t)getMidiNote __attribute__((swift_name("getMidiNote()")));
- (SGuitarNoteValue *)getNote __attribute__((swift_name("getNote()")));
- (int32_t)getOctave __attribute__((swift_name("getOctave()")));
@end

__attribute__((swift_name("KotlinComparable")))
@protocol SGuitarKotlinComparable
@required
- (int32_t)compareToOther:(id _Nullable)other __attribute__((swift_name("compareTo(other:)")));
@end

__attribute__((swift_name("KotlinEnum")))
@interface SGuitarKotlinEnum<E> : SGuitarBase <SGuitarKotlinComparable>
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer));
@property (class, readonly, getter=companion) SGuitarKotlinEnumCompanion *companion __attribute__((swift_name("companion")));
- (int32_t)compareToOther:(E)other __attribute__((swift_name("compareTo(other:)")));
- (BOOL)isEqual:(id _Nullable)other __attribute__((swift_name("isEqual(_:)")));
- (NSUInteger)hash __attribute__((swift_name("hash()")));
- (NSString *)description __attribute__((swift_name("description()")));
@property (readonly) NSString *name __attribute__((swift_name("name")));
@property (readonly) int32_t ordinal __attribute__((swift_name("ordinal")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NoteValue")))
@interface SGuitarNoteValue : SGuitarKotlinEnum<SGuitarNoteValue *>
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (instancetype)initWithName:(NSString *)name ordinal:(int32_t)ordinal __attribute__((swift_name("init(name:ordinal:)"))) __attribute__((objc_designated_initializer)) __attribute__((unavailable));
@property (class, readonly, getter=companion) SGuitarNoteValueCompanion *companion __attribute__((swift_name("companion")));
@property (class, readonly) SGuitarNoteValue *none __attribute__((swift_name("none")));
@property (class, readonly) SGuitarNoteValue *c __attribute__((swift_name("c")));
@property (class, readonly) SGuitarNoteValue *cSharp __attribute__((swift_name("cSharp")));
@property (class, readonly) SGuitarNoteValue *dFlat __attribute__((swift_name("dFlat")));
@property (class, readonly) SGuitarNoteValue *d __attribute__((swift_name("d")));
@property (class, readonly) SGuitarNoteValue *dSharp __attribute__((swift_name("dSharp")));
@property (class, readonly) SGuitarNoteValue *eFlat __attribute__((swift_name("eFlat")));
@property (class, readonly) SGuitarNoteValue *e __attribute__((swift_name("e")));
@property (class, readonly) SGuitarNoteValue *f __attribute__((swift_name("f")));
@property (class, readonly) SGuitarNoteValue *fSharp __attribute__((swift_name("fSharp")));
@property (class, readonly) SGuitarNoteValue *gFlat __attribute__((swift_name("gFlat")));
@property (class, readonly) SGuitarNoteValue *g __attribute__((swift_name("g")));
@property (class, readonly) SGuitarNoteValue *gSharp __attribute__((swift_name("gSharp")));
@property (class, readonly) SGuitarNoteValue *aFlat __attribute__((swift_name("aFlat")));
@property (class, readonly) SGuitarNoteValue *a __attribute__((swift_name("a")));
@property (class, readonly) SGuitarNoteValue *aSharp __attribute__((swift_name("aSharp")));
@property (class, readonly) SGuitarNoteValue *bFlat __attribute__((swift_name("bFlat")));
@property (class, readonly) SGuitarNoteValue *b __attribute__((swift_name("b")));
+ (SGuitarKotlinArray<SGuitarNoteValue *> *)values __attribute__((swift_name("values()")));
@property (class, readonly) NSArray<SGuitarNoteValue *> *entries __attribute__((swift_name("entries")));
- (NSString *)nameFlat __attribute__((swift_name("nameFlat()")));
- (NSString *)nameSharp __attribute__((swift_name("nameSharp()")));
@property (readonly) int32_t value __attribute__((swift_name("value")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("NoteValue.Companion")))
@interface SGuitarNoteValueCompanion : SGuitarBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) SGuitarNoteValueCompanion *shared __attribute__((swift_name("shared")));
- (SGuitarNoteValue * _Nullable)getByValueValue:(int32_t)value __attribute__((swift_name("getByValue(value:)")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("Scale")))
@interface SGuitarScale : SGuitarBase
- (instancetype)initWithRootNote:(SGuitarNoteValue *)rootNote semitones:(NSArray<SGuitarInt *> *)semitones __attribute__((swift_name("init(rootNote:semitones:)"))) __attribute__((objc_designated_initializer));
- (NSArray<SGuitarNoteValue *> *)getNotes __attribute__((swift_name("getNotes()")));
- (NSString *)testDescription __attribute__((swift_name("testDescription()")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinEnumCompanion")))
@interface SGuitarKotlinEnumCompanion : SGuitarBase
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
+ (instancetype)companion __attribute__((swift_name("init()")));
@property (class, readonly, getter=shared) SGuitarKotlinEnumCompanion *shared __attribute__((swift_name("shared")));
@end

__attribute__((objc_subclassing_restricted))
__attribute__((swift_name("KotlinArray")))
@interface SGuitarKotlinArray<T> : SGuitarBase
+ (instancetype)arrayWithSize:(int32_t)size init:(T _Nullable (^)(SGuitarInt *))init __attribute__((swift_name("init(size:init:)")));
+ (instancetype)alloc __attribute__((unavailable));
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable));
- (T _Nullable)getIndex:(int32_t)index __attribute__((swift_name("get(index:)")));
- (id<SGuitarKotlinIterator>)iterator __attribute__((swift_name("iterator()")));
- (void)setIndex:(int32_t)index value:(T _Nullable)value __attribute__((swift_name("set(index:value:)")));
@property (readonly) int32_t size __attribute__((swift_name("size")));
@end

__attribute__((swift_name("KotlinIterator")))
@protocol SGuitarKotlinIterator
@required
- (BOOL)hasNext __attribute__((swift_name("hasNext()")));
- (id _Nullable)next __attribute__((swift_name("next()")));
@end

#pragma pop_macro("_Nullable_result")
#pragma clang diagnostic pop
NS_ASSUME_NONNULL_END
