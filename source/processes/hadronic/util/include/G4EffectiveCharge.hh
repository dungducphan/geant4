//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
#ifndef G4EffectiveCharge_h
#define G4EffectiveCharge_h

#include "SystemOfUnits.h"
#include "PhysicalConstants.h"
#include "G4Material.hh"

class G4EffectiveCharge
{
  public:
  G4double GetCharge(const G4Material* material, G4double kineticEnergy,
            G4double particleMass, G4double ionCharge);
};

inline G4double G4EffectiveCharge::GetCharge(const G4Material* material, G4double kineticEnergy,
            G4double particleMass, G4double ionCharge)
{
  // This is cut and paste from low_energy electromagnetic to avoid coupling.
  // A design iteration is necessary for next time, to generate a process utility.
  
  // Original Author: V Ivanchenko.
  // The aproximation of ion effective charge from: 
  // J.F.Ziegler, J.P. Biersack, U. Littmark
  // The Stopping and Range of Ions in Matter,
  // Vol.1, Pergamon Press, 1985

  // Fast ions or hadrons
  G4double reducedEnergy = kineticEnergy * proton_mass_c2/particleMass ;
  if( (reducedEnergy > ionCharge * 10.0 * MeV) || 
      (ionCharge < 1.5) ) return ionCharge*ionCharge ;

  static G4double vFermi[92] = {
    1.0309,  0.15976, 0.59782, 1.0781,  1.0486,  1.0,     1.058,   0.93942, 0.74562, 0.3424,
    0.45259, 0.71074, 0.90519, 0.97411, 0.97184, 0.89852, 0.70827, 0.39816, 0.36552, 0.62712,
    0.81707, 0.9943,  1.1423,  1.2381,  1.1222,  0.92705, 1.0047,  1.2,     1.0661,  0.97411,
    0.84912, 0.95,    1.0903,  1.0429,  0.49715, 0.37755, 0.35211, 0.57801, 0.77773, 1.0207,
    1.029,   1.2542,  1.122,   1.1241,  1.0882,  1.2709,  1.2542,  0.90094, 0.74093, 0.86054,
    0.93155, 1.0047,  0.55379, 0.43289, 0.32636, 0.5131,  0.695,   0.72591, 0.71202, 0.67413,
    0.71418, 0.71453, 0.5911,  0.70263, 0.68049, 0.68203, 0.68121, 0.68532, 0.68715, 0.61884,
    0.71801, 0.83048, 1.1222,  1.2381,  1.045,   1.0733,  1.0953,  1.2381,  1.2879,  0.78654,
    0.66401, 0.84912, 0.88433, 0.80746, 0.43357, 0.41923, 0.43638, 0.51464, 0.73087, 0.81065,
    1.9578,  1.0257} ;

  static G4double lFactor[92] = {
    1.0,  1.0,  1.1,  1.06, 1.01, 1.03, 1.04, 0.99, 0.95, 0.9,
    0.82, 0.81, 0.83, 0.88, 1.0,  0.95, 0.97, 0.99, 0.98, 0.97,
    0.98, 0.97, 0.96, 0.93, 0.91, 0.9,  0.88, 0.9,  0.9,  0.9,
    0.9,  0.85, 0.9,  0.9,  0.91, 0.92, 0.9,  0.9,  0.9,  0.9,
    0.9,  0.88, 0.9,  0.88, 0.88, 0.9,  0.9,  0.88, 0.9,  0.9,
    0.9,  0.9,  0.96, 1.2,  0.9,  0.88, 0.88, 0.85, 0.9,  0.9, 
    0.92, 0.95, 0.99, 1.03, 1.05, 1.07, 1.08, 1.1,  1.08, 1.08,
    1.08, 1.08, 1.09, 1.09, 1.1,  1.11, 1.12, 1.13, 1.14, 1.15,
    1.17, 1.2,  1.18, 1.17, 1.17, 1.16, 1.16, 1.16, 1.16, 1.16,
    1.16, 1.16} ; 

  static G4double c[6] = {0.2865,  0.1266, -0.001429,
                          0.02402,-0.01135, 0.001475} ;

  // get elements in the actual material,
  const G4ElementVector* theElementVector = material->GetElementVector() ;
  const G4double* theAtomicNumDensityVector = 
                         material->GetAtomicNumDensityVector() ;
  const G4int NumberOfElements = material->GetNumberOfElements() ;
  
  //  loop for the elements in the material
  //  to find out average values Z, vF, lF
  G4double z = 0.0, vF = 0.0, lF = 0.0, norm = 0.0 ; 

  if( 1 == NumberOfElements ) 
  {
    z = material->GetZ() ;
    G4int iz = G4int(z) - 1 ;
    if(iz < 0) iz = 0 ;
    else if(iz > 91) iz = 91 ;
    vF   = vFermi[iz] ;
    lF   = lFactor[iz] ;

  } 
  else 
  {
    for (G4int iel=0; iel<NumberOfElements; iel++)
    {
      const G4Element* element = (*theElementVector)[iel] ;
      G4double z2 = element->GetZ() ;
      const G4double weight = theAtomicNumDensityVector[iel] ;
      norm += weight ;
      z    += z2 * weight ;
      G4int iz = G4int(z2) - 1 ;
      if(iz < 0) iz = 0 ;
      else if(iz > 91) iz =91 ;
      vF   += vFermi[iz] * weight ;
      lF   += lFactor[iz] * weight ;
    }
    z  /= norm ;
    vF /= norm ;
    lF /= norm ;
  }

  // Helium ion case
  if( ionCharge < 2.5 ) 
  {
    G4double theHeMassAMU(4.0026);
    G4double e = log(G4std::max(1.0, kineticEnergy / (keV*theHeMassAMU) )) ; 
    G4double x = c[0] ;
    G4double y = 1.0 ;
    for (G4int i=1; i<6; i++) 
    {
      y *= e ;
      x += y * c[i] ;
    }
    G4double q = 7.6 -  e ; 
    q = 1.0 + ( 0.007 + 0.00005 * z ) * exp( -q*q ) ;
    return  4.0 * q * q * (1.0 - exp(-x)) ;

    // Heavy ion case
  } 
  else 
  {

    // v1 is ion velocity in vF unit
    G4double v1 = sqrt( reducedEnergy / (25.0 * keV) )/ vF ;
    G4double y ;
    G4double z13 = pow(ionCharge, 0.3333) ;

    // Faster than Fermi velocity
    if ( v1 > 1.0 ) 
    {
      y = vF * v1 * ( 1.0 + 0.2 / (v1*v1) ) / (z13*z13) ;

      // Slower than Fermi velocity
    } 
    else 
    {
      y = 0.6923 * vF * (1.0 + 2.0*v1*v1/3.0 + v1*v1*v1*v1/15.0) / (z13*z13) ;
    }

    G4double y3 = pow(y, 0.3) ;
    G4double q = 1.0 - exp( 0.803*y3 - 1.3167*y3*y3 - 
                            0.38157*y - 0.008983*y*y ) ;     
    if( q < 0.0 ) q = 0.0 ;

    G4double s = 7.6 -  log(G4std::max(1.0, reducedEnergy/keV)) ; 
    s = 1.0 + ( 0.18 + 0.0015 * z ) * exp( -s*s )/ (ionCharge*ionCharge) ;

    // Screen length according to
    // J.F.Ziegler and J.M.Manoyan, The stopping of ions in compaunds,
    // Nucl. Inst. & Meth. in Phys. Res. B35 (1988) 215-228.

    G4double lambda = 10.0 * vF * pow(1.0-q, 0.6667) / (z13 * (6.0 + q)) ;
    G4double qeff   = ionCharge * s *
      ( q + 0.5*(1.0-q) * log(1.0 + lambda*lambda) / (vF*vF) ) ;
    if( 1.0 > qeff ) qeff = 1.0 ; 
    return qeff*qeff ;    
  }
}

#endif