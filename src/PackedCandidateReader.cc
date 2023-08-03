#include "Haamm/HaNaMiniAnalyzer/interface/PackedCandidateReader.h"
#include <Math/Point3D.h> 

PackedCandidateReader::PackedCandidateReader( edm::ParameterSet const& iPS, edm::ConsumesCollector && iC , VertexReader* vertices) :
  BaseEventReader< pat::PackedCandidateCollection >( iPS , &iC )
{

  Vertices = vertices;

  nParticles = nNeutralHadrons = nPhotons = nEles = nMus = nChargedHadrons = 0;
  memset(Pt, 0, sizeof(Pt));
  memset(Eta, 0, sizeof(Eta));
  memset(Charge, 0, sizeof(Charge));
  memset(Energy, 0, sizeof(Energy));
  memset(P, 0, sizeof(P));
  memset(Phi, 0, sizeof(Phi));
  memset(particleDxy_, 0, sizeof(particleDxy_));
  memset(particleDz_, 0, sizeof(particleDz_));
  memset(type, 0, sizeof(type));
  memset(nearestVertexDz, 0, sizeof(nearestVertexDz));
  memset(nearestVertexIdx, -1, sizeof(nearestVertexIdx));

}

double PackedCandidateReader::Read(const edm::Event& iEvent)
{
  BaseEventReader<pat::PackedCandidateCollection>::Read(iEvent);

  nParticles = nNeutralHadrons = nPhotons = nEles = nMus = nChargedHadrons = 0;

  for (auto cand : *handle) {
    int id = abs(cand.pdgId());
    if (id == 11) {
      nEles++;
    } else if (id == 13) {
      nMus++;
    } else if (id == 211) {
      nChargedHadrons++;
    } else if (id == 130) {
      nNeutralHadrons++;
    } else if (id == 22) {
      nPhotons++;
    }

    Pt[nParticles] = cand.pt();
    Eta[nParticles] = cand.eta();
    Charge[nParticles] = cand.charge();
    Energy[nParticles] = cand.energy();
    P[nParticles] = cand.p();
    Phi[nParticles] = cand.phi();
    particleDxy_[nParticles] = cand.dxy();
    particleDz_[nParticles] = cand.dz();
    type[nParticles] = cand.pdgId();

    // Update the minimum dz value for the corresponding cand.
    for (size_t i = 0; i < Vertices->goodVertices.size(); ++i)
      {
	auto vtx = Vertices->goodVertices[i];
	auto pnt = vtx->position();
	float dzValue = cand.dz(pnt);

	if (dzValue < nearestVertexDz[nParticles])
	  {
	    nearestVertexDz[nParticles] = dzValue;
            nearestVertexIdx[nParticles] = i;
	  }
      }

    nParticles++;
     
  }
  return nParticles;
  std::cout << "PackedCandidateReader" << std::endl;

}
