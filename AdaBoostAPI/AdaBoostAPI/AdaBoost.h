#pragma once
#ifndef ADABOOST_H
#define ADABOOST_H
#include "general.h"
#include "StrongClassfier.h"
#include "WeakClassifier.h"

class AdaBoost
{

public:
	AdaBoost(AdaBoostType::C_DATAS& data, AdaBoostType::C_LABELS label) :_data(data), _label(label){ Init(); };
	~AdaBoost();

	void Train(C_UINT32 weakSize);
	AdaBoostType::LABELS Predict(AdaBoostType::C_DATAS& data) const;
	AdaBoostType::LABEL Predict(AdaBoostType::C_DATA& data) const;
private:
	void Init();
	void ProcessError(WeakClassifier& weakClassifier, AdaBoostType::LABELS& pridect);
	double CalcError(AdaBoostType::C_LABELS& pridect);
	void UpdateWeights(const WeakClassifier& weakClassifier, AdaBoostType::C_LABELS& pridect);

	AdaBoostType::C_DATAS _data;
	AdaBoostType::C_LABELS _label;

	StrongClassfier* _strongClassfier;
	std::vector<double>* _dataWeights;
	UINT32 _dimensionSize;
	UINT32 _dataSize;

};

#endif // !ADABOOST_H
