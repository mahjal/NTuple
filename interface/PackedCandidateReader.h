#ifndef PackedCandidateReader_H
#define PackedCandidateReader_H


#include "BaseEventReader.h"
#include "VertexReader.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include <bitset>

#define MAX_Particles 40000

class PackedCandidateReader : public BaseEventReader<pat::PackedCandidateCollection> {
 public:
  PackedCandidateReader(edm::ParameterSet const& iPS, edm::ConsumesCollector&& iC , VertexReader* vertices);
  double Read(const edm::Event& iEvent) override;

  VertexReader* Vertices;

  float Pt[MAX_Particles];
  float Eta[MAX_Particles];
  float Energy[MAX_Particles];
  float P[MAX_Particles];
  float Phi[MAX_Particles];
  //  float dxy[MAX_Particles];
  float dz[MAX_Particles];
  int type[MAX_Particles];
  int Charge[MAX_Particles];
  int nEles;
  int nMus;
  int nChargedHadrons;
  int nNeutralHadrons;
  int nPhotons;
  int nParticles;

  float particleDxy_[MAX_Particles];  
  float particleDz_[MAX_Particles];  
  //reco::Candidate::Point vertex_[MAX_Particles];              
  int nearestVertexIdx[MAX_Particles];
  float nearestVertexDz[MAX_Particles];
  float nearestVertexDxy[MAX_Particles];



  int size() const {
    return handle->size();
  }
};

#endif
