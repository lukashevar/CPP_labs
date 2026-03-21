#include "MailQueue.h"
#include <stdexcept>

void MailQueue::addSubmission(const Submission& sub) {
	queueSubs.push(sub);
}

Submission MailQueue::getNextSubmission() {
	if (queueSubs.empty()) {
		throw std::runtime_error("Mail queue is empty");
	}

	Submission next = queueSubs.front();
	queueSubs.pop();
	return next;
}

bool MailQueue::isEmpty() const {
	return queueSubs.empty();
}

