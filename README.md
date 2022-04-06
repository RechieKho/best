# Best Scripting Language

This project is started on April fool 2022 and ended on April fool + 3 days 2022. 
I was thinking about that newbies in programming always search which language is the BEST language so I think I should just simple make one and name it "BEST".

This is still not yet done.

But sadly, I can't abandon my current project, which is a game. So I need to stop suffocating in C++. 

## Completion list

[ x ] Basic Data types
[ x ] Garbage Collector
[  ] Log
[  ] Lexer
[  ] Analyzer

## How to play
1. clone this git.
2. make sure cmake installed
3. `$ mkdir build && cd build && cmake .. && cmake --build .`
4. `$ cd Main && ./main`

## Documentation

| Directory | purpose |
| ----- | ----- |
| Types | types (Array, Object and etc.) |
| Log | Log to console |
| Cleaner | Garbage Collector |
| BLexer | Lexer |


### Types
1. `Getable` is the abstract base class for all the data type. Object that is `Getable` can 'access' its 'property' through the `Get` method.
2. `Setable` is derived from `Getable` and can set its property through `Set`.

Why design this way? I want to obey Python's Object philosophy ~~there is no such philosophy!~~ which is "everything is an object".
Thus, even primitives such as `Integer` is derived from `Getable` as it emulates the property. 

```cpp
Integer *i = new Integer(23);
Float *f = new Float(2.3);
Array *arr = new Array(3  , new Integer(1), new Integer(2), new Integer(3));
Object *o = new Object(2, 
    new KeyValuePair(new String("Key"), new String("Value")),
    new KeyValuePair(new String("foo"), new String("Bar"))
);
std::cout << o->ToString() << std::endl; // print out the object
Cleaner::Flush(); // all those Integers and Objects are gone now :'(
```

### Cleaner
I think the most complete part of this project is the Garbage Collector (just a few lines of code). 
All the `Cleanable`s are automatically registered to the cleaning list (`Getable` is a `Cleanable`). 
`Cleanable` have a `ref_count` which count the number the object is referenced.

`Array`s and `Object`s automatically add up and reduces the `ref_count` of its element. 

For an example, when you assign an `Integer` to an `Array`. The `Integer`'s `ref_count` automatically increases.

Assigning `Cleanable` to a variable won't change the `ref_count` (for now).

### Log
The most incomplete part of the project. 

### BLexer
It works but can't differentiate numbers and word for now.
Tokens are all in `BToken.hpp`