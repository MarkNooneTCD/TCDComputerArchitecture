#pragma once

//
// fib32.h
//
// Copyright (C) 2012 - 2017 jones@scss.tcd.ie
//
// example of mixing C++ and IA32 assembly language
//

//
// NB: "extern C" to avoid procedure name mangling by compiler
//

extern "C" _int64 minx64(_int64, _int64, _int64);
extern "C" _int64 px64(_int64, _int64, _int64, _int64);
extern "C" _int64 gcdx64(_int64, _int64);
extern "C" _int64 qx64(_int64, _int64, _int64, _int64, _int64);
extern "C" _int64 qnsx64(_int64, _int64, _int64, _int64, _int64);


// eof