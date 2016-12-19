# Low Level Memory Model for mal-x64 Data Structures

Note: details are subject to change as progress is made towards a GC implementation.

All non byte primitives are stored in little endian format per x64 requirements.

## Definitions
|Name|Definition|
|----|----------|
|BYTE|An 8 bit value|
|WORD|2 BYTES|
|DWORD|4 BYTES|
|QWORD|8 BYTES|
|Reference|All references are 64 bit pointers into the process address space.

## Data Structures
All structures are peristent with the exception of Atom. All structures are non-recursive
except for Atom which allows for cycles in the heap graph.

All data structures are aligned on 8 byte boundaries per x64 performance best practices.

Each data structure object will be divided into the header and the payload. The header will
be at least 8 bytes followed by 0 or more bytes for the payload.

## References
All data references point to the start of the payload. The header precedes the payload within
the process address space.

## Header
The header contains the type tag as well as other metadata. The minimal header is 8 bytes and
is laid out as follows:

|Offset|x64 Type|Description|
|------|--------|-----------|
|-8|BYTE|The type tag|
|-7|BYTE|Flags|
|-6 to -1|*|Six bytes are reserved for use by the data type.|

The header should be sufficient to calculate the total space in use by the data structure.

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
Symbols are a subtype of string and have the same mechanics but different semantics.

### Cons Cell (List)
The cons cell forms the foundation for the linked list. It is made up two components, the
`car` which is a reference to the data and `cdr` which is a reference to the rest of the
list or Nil if there no more elements. The empty list and Nil are equivalent.

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