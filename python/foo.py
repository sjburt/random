#!/usr/env python
foo = 'bar'

def printfoo():
    print foo

def printfoo2():
    print locals()
    foo = 'foo'
    print locals()
