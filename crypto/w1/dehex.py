#!/usr/bin/python

import binascii
import itertools
import string

possible_letters = ' ' + string.digits + string.punctuation + string.letters

def xor(a, b):
    return a ^ b


def check_rl(rl):
    for l in rl:
        if chr(l) not in possible_letters:
            return False
    return True


def decrypt_based_on_index(ii, ll):
    iiguess = 0
    done = False
    while not done:
        key = ll[ii] ^ ord(possible_letters[iiguess])
        rl = [e ^ key for e in ll]
        if check_rl(rl):
            return rl
        else:
            iiguess += 1
        if iiguess >= len(possible_letters):
            return rl


def decrypt(ll):
    """ decrypt will take a list of bytes which have been xor'd with an unknown key,
        and attempt to return a list which have been decrypted"""
    t = len(ll)
    possible_spaces = [0] * t
    for (i, j) in itertools.combinations(range(0, 11), 2):
        if xor(ll[i], ll[j]) >= 0x40:
            possible_spaces[i] += 1
            possible_spaces[j] += 1

    most_likely = possible_spaces.index(max(possible_spaces))
    return decrypt_based_on_index(most_likely, ll)


def fix_unp(a, b, c):
    tupe = find_space(a, b, c)
    if tupe is None:
        return None
    (a, b, c) = tupe
    if chr(a) not in string.printable:
        return None
    if chr(b) not in string.printable:
        return None
    if chr(c) not in string.printable:
        return None

    return tupe


def find_space(a, b, c):
    ''' a,b,c are cypher characters '''
    ab = xor(a, b)
    ac = xor(a, c)
    bc = xor(b, c)

    if ab >= 0x40:
        if ac >= 0x40:  # then a is a space
            rA = 0x20
            rB = xor(0x20, ab)
            rC = xor(0x20, ac)
            return (rA, rB, rC)
        if bc >= 0x40:  # then b is a space
            rB = 0x20
            rA = xor(0x20, ab)
            rC = xor(0x20, ac)
            return (rA, rB, rC)
    if ac >= 0x40:
        if ab >= 0x40:  # then a is a space
            rA = 0x20
            rB = xor(0x20, ab)
            rC = xor(0x20, ac)
            return (rA, rB, rC)
        if bc >= 0x40:  # then c is a space
            rC = 0x20
            rA = xor(0x20, ac)
            rB = xor(0x20, bc)
            return (rA, rB, rC)
    if bc >= 0x40:
        if ab >= 0x40:  # then b is a space
            rA = xor(0x20, ab)
            rB = 0x20
            rC = xor(0x20, bc)
            return (rA, rB, rC)
        if ac >= 0x40:  # then c is a space
            rC = 0x20
            rA = xor(0x20, ac)
            rB = xor(0x20, bc)
            return (rA, rB, rC)
    return None


def xor_strings(xs, ys):
    ''' xor_strings does a bitwise xor on two strings) '''
    return "".join(chr(ord(x) ^ ord(y)) for x, y in zip(xs, ys))


def zeros(ss):
    ds = [bytearray([0 for i in j]) for j in ss]
    return ds


def print_results(ll):
    i = 1
    for l in ll:
        print i, str(l)
        i += 1

cryptos = []
for i in xrange(1, 12):
    cryptos.append(open(str(i)).read()[0:-1])
    print len(cryptos[-1])
ss = []
i = 0
for s in cryptos:
    ss.append(bytearray(binascii.a2b_hex(s)))

# for (i, j, k) in itertools.combinations(xrange(0, 11), 3):
#    for x in xrange(0, min(len(ss[i]), len(ss[j]), len(ss[k]))):
#        tupe = fix_unp(ss[i][x], ss[j][x], ss[k][x])
#        if tupe is not None:
#            (d, e, f) = tupe
# use what we know already
#            ds[i][x] = d
#            ds[j][x] = e
#            ds[k][x] = f
#
ds = ['' for qqq in range(len(ss))]
print ds
for ii in xrange(len(ss[10])):
    ll = [s[ii] for s in ss]
    ll = decrypt(ll)
    for jj in xrange(len(ll)):
        ds[jj] = ds[jj] + chr(ll[jj])

print_results(ds)
print ds[10]
