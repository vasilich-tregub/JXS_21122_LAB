#!/usr/bin/python

# $Id: jp2utils.py,v 1.19 2016/06/01 16:18:59 thor Exp $

class JP2Error(Exception):
    def __init__(self, reason):
        Exception.__init__(self, reason)

def print_hex(buffer, indent = 0, sec_indent = -1):
    if sec_indent == -1:
        sec_indent = indent
    buff = ""
    for i in range(len(buffer)):
        if i % 16 == 0:
            if i != 0:
                print ("  ",buff)
                indent = sec_indent
                buff   = ""
            for j in range(indent):
                print (" "),
        if ord(buffer[i]) >= 32 and ord(buffer[i]) < 127:
            buff += buffer[i]
        else:
            buff += "."
        print ("%02x" % (ord(buffer[i]))),
    for j in range((16 - (len(buffer) % 16)) % 16):
        print ("  "),
    print ("  ",buff)
    
def print_indent(buffer, indent = 0, nl = 1):
    for i in range(indent):
        print (" "),
    if nl:
        print (buffer)
    else:
        print (buffer),

def ieee_float_to_float(data):
    if data != 0:
        sign      = data >> 31
        exponent  = (data >> 23) & 0xff
        mantissa  = data & ((1 << 23) - 1)
        if exponent == 255:
             return NotImplemented
        elif exponent != 0:
            mantissa += 1 << 23
        else:
            exponent += 1
        number    = 0.0 + mantissa
        exponent -= 127 + 23
        if exponent > 0:
            number *= 2.0 ** exponent
        elif exponent < 0:
            number /= 2.0 ** (-exponent)
        if sign != 0:
            number = -number
        return number
    else:
        return 0.0


def ieee_double_to_float(data):
    if data != 0:
        sign      = data >> 63
        exponent  = (data >> 51) & ((1 << 11) - 1)
        mantissa  = data & ((1 << 52) - 1)
        if exponent == 0x7ff:
            return NotImplemented
        elif exponent != 0:
            mantissa += 1 << 52
        else:
            exponent += 1
        number    = 0.0 + mantissa
        exponent -= 1023 + 52
        if exponent > 0:
            number *= 2.0 ** exponent
        elif exponent < 0:
            number /= 2.0 ** (-exponent)
        if sign != 0:
            number = -number
        return number
    else:
        return 0.0

# This is a fake substitution for the file class that operates on a memory
# buffer.

class Buffer:
    def __init__(self, buffer):
        self.offset = 0
        self.buffer = buffer

    def eof_reached(self):
        return self.offset >= len(self.buffer)

    def rest_len(self):
        return len(self.buffer) - self.offset

    def __len__(self):
        return len(self.buffer)

    def __getitem__(self,offset):
        return self.buffer[offset]
    
    def read(self, length = -1):
        if self.eof_reached():
            return ""
        if length == -1 or length > self.rest_len():
            length = self.rest_len()
        ret = self.buffer[self.offset:self.offset + length]
        self.offset = self.offset + length
        return ret

    def tell(self):
        return self.offset

    def seek(self,where):
        self.offset = where

def ordw(buffer):
    return (buffer[0] << 8) + \
           (buffer[1] << 0)

def ordl(buffer):
    return (buffer[0] << 24) + \
           (buffer[1] << 16) + \
           (buffer[2] <<  8) + \
           (buffer[3] <<  0)

def ordq(buffer):
    return (ord(buffer[0]) << 56) + \
           (ord(buffer[1]) << 48) + \
           (ord(buffer[2]) << 40) + \
           (ord(buffer[3]) << 32) + \
           (ord(buffer[4]) << 24) + \
           (ord(buffer[5]) << 16) + \
           (ord(buffer[6]) <<  8) + \
           (ord(buffer[7]) <<  0)
            
def chrw(i):
    return chr((i >> 8) & 255)+chr(i & 255)

def chrl(i):
    return chr((i >> 24) & 255) + \
        chr((i >> 16) & 255) + \
        chr((i >>  8) & 255) + \
        chr((i >>  0) & 255)

def chrq(i):
    return chr((i >> 56) & 255) + \
        chr((i >> 48) & 255) + \
        chr((i >> 40) & 255) + \
        chr((i >> 32) & 255) + \
        chr((i >> 24) & 255) + \
        chr((i >> 16) & 255) + \
        chr((i >>  8) & 255) + \
        chr((i >>  0) & 255)

def version(buffer):
    return ord(buffer[0])

def flags(buffer):
    return (ord(buffer[1]) << 16) + \
           (ord(buffer[2]) <<  8) + \
           (ord(buffer[3]) <<  0)

def fromCString(buffer):
    res = ""
    for i in range(len(buffer)):
        ch = ord(buffer[i:i+1])
        if ch == 0:
            return res
        elif ch < 32 or ch > 127:
            res = "%s\\%03o" % (res,ch)
        else:
            res = "%s%c" % (res,ch)            
    return res
        
def secsToTime(total):
    seconds = total % 60
    total   = total / 60
    minutes = total % 60
    total   = total / 60
    hours   = total % 24
    total   = total / 24
    year    = 1904
    while True:
        leap = False
        if year % 400 == 0:
            leap = True
        elif leap % 100 == 0:
            leap = False
        elif leap % 4 == 0:
            leap = True
        daysperyear = 365
        if leap:
            daysperyear = 366
        if total < daysperyear:
            break
        total = total - daysperyear
        year  = year + 1
    dayspermonth = [31,28,31,30,31,30,31,31,30,31,30,31]
    monthnames   = ["Jan","Feb","Mar","Apr","Mai","Jun","Jul","Aug","Sep","Oct","Nov","Dez"]
    if leap:
        dayspermonth[1] = 29
    month = 0
    for t in dayspermonth:
        if total < t:
            break
        total = total - t
        month = month + 1
    return "%02d:%02d:%02d %2d-%s-%4d" % \
           (hours,minutes,seconds,total+1,monthnames[month],year)
