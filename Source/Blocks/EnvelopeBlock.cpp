/*
  ==============================================================================

    EnvelopeBlock.cpp
    
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#include "EnvelopeBlock.h"

void EnvelopeBlock::updateEnvelope(const float attack, const float decay, const float sustain, const float release)
{
    mEnvelopeParameters.attack = attack;
    mEnvelopeParameters.decay = decay;
    mEnvelopeParameters.sustain = sustain;
    mEnvelopeParameters.release = release;
    
    setParameters(mEnvelopeParameters);
    
}
