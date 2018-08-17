#!/usr/bin/env ruby
# units.rb

# This is the module including all the constants to convert to standard units.
# @author Enritoc Bertolazzi & Francesco Biral
module UNITS
  VERSION = "0.0.1"
  M    = 1 ;
  MM   = 0.001 ;
  CM   = 0.01 ;
  S    = 1.0 ;
  MIN  = 60.0 ;
  KG   = 1 ;
  N    = KG*M/S**2 ;
  NM   = N*M ;
  WATT = N*M/S ;
  HZ   = 1/S ;
  RAD  = 1 ;
  RADS = 1 ;
  RPM  = Math::PI/30.0 ;
  DEG  = Math::PI/180.0 ;
end
