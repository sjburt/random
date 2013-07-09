#!/usr/bin/python
import binascii

def xor_strings(xs,ys):
    ''' xor_strings does a bitwise xor on two strings) '''
    return "".join(chr(ord(x)^ord(y)) for x,y in zip(xs,ys))

cyph = binascii.a2b_hex("09e1c5f70a65ac519458e7e53f36")

plain = "attack at dawn"

print len(cyph), len(plain)

key = xor_strings(plain,cyph)

plain2 = "attack at dusk"

cyph2 = xor_strings(plain2,key)

print binascii.b2a_hex(cyph2)

delta = xor_strings(plain,plain2)

cyph2 = xor_strings(cyph,delta)

print binascii.b2a_hex(cyph2)
