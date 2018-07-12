#--------------------------------------------------------------------------#
#  file: pointcar_Data.rb                                                  #
#                                                                          #
#  version: 1.0   date 13/7/2018                                           #
#                                                                          #
#  Copyright (C) 2018                                                      #
#                                                                          #
#      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti                #
#      Dipartimento di Ingegneria Industriale                              #
#      Universita` degli Studi di Trento                                   #
#      Via Sommarive 9, I-38123, Trento, Italy                             #
#      email: enrico.bertolazzi@unitn.it                                   #
#             francesco.biral@unitn.it                                     #
#             paolo.bosetti@unitn.it                                       #
#--------------------------------------------------------------------------#

# User defined classes initialization
# User defined classes: R O A D

mechatronix do |data|

data.Road = 
{
  :roadWidth => 3.7,
  :gridSize  => 5,
  :theta0    => 0,
  :s0        => 0,
  :x0        => 0,
  :y0        => 0,
  :is_SAE    => true,
  :segments  => [
    { :radius => 45.2707044337391/347.327792187656, :angle => 347.327792187656 },
    { :length => 244.134389610089  },
    { :radius => 59.358551236732/347.327792187656, :angle => -347.327792187656 },
    { :length => 201.644854584327 },
    { :radius => 142.894358535785/49.7836502135641, :angle => 49.7836502135641 },
    { :length => 133.43893827313 },
    { :radius => 67.1863934651959/57.8879653646094, :angle => -57.8879653646094 },
    { :length => 45.9584134622707 },
    { :radius => 75.6533188312851/46.3103722916875, :angle => 46.3103722916875 },
    { :length => 334.716783157046 },
    { :radius => 71.4573675497968/69.4655584375313, :angle => -69.4655584375313 },
    { :length => 34.6598403824062 },
    { :radius => 79.9150308414277/69.4655584375313, :angle => 69.4655584375313 },
    { :length => 263.472674871652 },
    { :radius => 81.3041104583168/81.0431515104532, :angle => 81.0431515104532 },
    { :length => 48.7678321973459 },
    { :radius => 129.057513950613/92.6207445833751, :angle => -92.6207445833751 },
    { :length => 163.432545543426 },
    { :radius => 155.737382531577/92.6207445833751, :angle => 92.6207445833751 },
    { :length => 132.80865410624 },
    { :radius => 91.6653616029976/69.4655584375313, :angle => 69.4655584375313 },
    { :length => 276.98025270983 },
    { :radius => 96.1313023549464/64.8345212083625, :angle => 64.8345212083625 },
    { :length => 35.6152233627838 },
    { :radius => 78.3247326569311/57.8879653646094, :angle => -57.8879653646094 },
    { :length => 323.774799943827 },
    { :radius => 218.995961770854/62.5190025937782, :angle => 62.5190025937782 },
    { :length => 120.082100696761 },
    { :radius => 35.1331323872273/57.8879653646094, :angle => -57.8879653646094 },
    { :length => 51.5168158965805 },
    { :radius => 61.7963292341664/104.198337656297, :angle => 104.198337656297 },
    { :length => 380.85511241567 },
    { :radius => 265.379041347039/78.7276328958688, :angle => -78.7276328958688 },
    { :length => 543.929215677558 }
  ],
} ;

end

# EOF
