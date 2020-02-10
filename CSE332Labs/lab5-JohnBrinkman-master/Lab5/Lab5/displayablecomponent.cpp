#include "stdafx.h"
#include "displayablecomponent.h"

using namespace std;

DisplayableComponent::DisplayableComponent(shared_ptr<DisplayableComponent> p) : parent(p) {}

// zero out all shared_ptr so resources are cleaned up, objects reference eachother in cycles..also, objects aren't shared between composites
DisplayableComponent::~DisplayableComponent() {
	for (size_t i = 0; i < children.size(); ++i) {
		children[i] = nullptr;
	}
	children.clear();
	parent = nullptr;
}

shared_ptr<DisplayableComponent> DisplayableComponent::addComponent(shared_ptr<DisplayableComponent> comp) {
	children.push_back(comp);
	return comp;
}
shared_ptr<DisplayableComponent> DisplayableComponent::removeComponent(unsigned int index) {
	if (index < children.size()) {
		shared_ptr<DisplayableComponent> removed = children[index];
		children[index] = nullptr;
		return removed;
	}
	else {
		return nullptr;
	}
}


shared_ptr<DisplayableComponent> DisplayableComponent::getParent() {
	return parent;
}

shared_ptr<DisplayableComponent> DisplayableComponent::getChild(unsigned int index) {
	if (index < children.size()) {
		return children[index];
	}
	else {
		return nullptr;
	}
}