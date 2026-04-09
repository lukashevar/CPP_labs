#pragma once
#include <queue>
#include "Submission.h"

class MailQueue {
private:
	std::queue<Submission> queueSubs;

public:
	void addSubmission(const Submission& sub);
	Submission getNextSubmission();
	bool isEmpty() const;
};
