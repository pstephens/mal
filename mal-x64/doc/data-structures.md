# Low Level Memory Model for mal-x64 Data Structures

Note: details are subject to change as progress is made towards a GC implementation.

All non byte primitives are stored in little endian format per x64 requirements.

## Definitions
|Name|Definition|
|----|----------|
|OBJECT|A single entity in the heap. Includes bytes for the header, payload, and suffix.|
|BYTE|An 8 bit value|
|WORD|2 BYTES|
|DWORD|4 BYTES|
|QWORD|8 BYTES|
|Reference|All references are 64 bit pointers into the process address space.

## OBJECTS
All OBJECTS are effectively immutable with the exception of Atom. All OBJECTS are
non-recursive except for the Atom which allows for cycles in the heap graph.

All OBJECTS have 8 byte alignment per x64 performance guidance.

Each OBJECT will be divided into the header, the payload, and the optional
suffix. The header will be exactly 8 bytes, followed by the payload, and then the
suffix. The total bytes for the OBJECT must be calculated from the header.

## References
All OBJECT references point to the start of the payload. The header precedes the payload
within the process address space.

## Header
The header contains the type tag as well as other metadata. The header is exactly 8 bytes and
is laid out as follows:

|Offset|x64 Type|Description|
|------|--------|-----------|
|-8|BYTE|The type tag|
|-7|BYTE|Flags|
|-6 to -1|*|Six bytes are reserved for use by the data type.|

The header is sufficient to calculate the total bytes used by the OBJECT.

### Data Type Tags
|Type|Description|
|----|-----------|
|0   |Boolean|
|10  |Number|
|20  |String|
|21  |String Span|
|30  |Symbol|
|40  |Keyword|
|50  |Cons Cell|
|60  |Vector Parent|
|61  |Vector Span|
|62  |Vector Leaf|
|70  |Map Parent|
|71  |Map Leaf|
|80  |Atom|
|90  |Built-in Function|
|91  |User defined Function|
|100 |Macro|

## Details
### Nil
The Nil value does not take space on the heap. It is a 64 bit reference with the value 0.

### Boolean
Boolean values can either be True or False. The payload is a 64 bit integer and is either 0
for False or 1 for True.

### Number
The number payload is a 64 bit signed integer.

### String
The string payload is an immutable string of ASCII bytes between 0 and 2^31 - 1 bytes in
length. The length is stored in the header in a DWORD at offset -4.

### String Span
This type represents a string fragment and reduces the cost to make a slice of an existing
string. The payload contains a reference to the underlying string as well as an offset and
a length. The payload is laid out as follows:

|Offset|x64 Type|Description|
|------|--------|-----------|
|+0 to +7|Reference|The reference to the string|
|+8 to +11|DWORD|The offset into the referenced string. This can be between 0 and 2^31 -1|
|+12 to +15|DWORD|The length of the span. This can be between 0 and 2^31 - 1|

The combined offset and length cannot exceed the referenced string's length.

### Symbol
Symbols are a subtype of string and have the same mechanics but different semantics.

### Keyword
Keywords are a subtype of string and have the same mechanics but different semantics.

### Cons Cell (List)
The cons cell provides the foundation for the linked list. It is made up two components: the
`car` which is a reference to the data and `cdr` which is a reference to the next cons cell
in the list. The final cons cell in the list is special and has a Nil reference for both
`car` and `cdr`. All `cdr` values must reference either another cons cell or Nil; no other
reference type is allowed. `car` may reference any valid type.

|Offset|x64 Type|Description|
|------|--------|-----------|
|+0 to +7|Reference|The CAR reference|
|+8 to +15|Reference|The CDR reference|

### Vector
TODO

### Map
TODO

### Atom
TODO

### Function
TODO

### Macro
TODO