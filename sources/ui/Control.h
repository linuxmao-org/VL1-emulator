#pragma once
#include "Widget.hpp"
#include <vector>
#include <cstdint>

class CControlListener;

class CControl : public Widget
{
public:
	CControl(Widget *group) : Widget(group) {}
	virtual ~CControl() {}

	intptr_t getTag() const noexcept { return fTag; }
	void setTag(intptr_t tag) noexcept { fTag = tag; }

	void addListener(CControlListener *cl);
	void removeListener(CControlListener *cl);

protected:
	void reportValueChanged(double value);
	void reportTriggered();

private:
	intptr_t fTag = 0;
	std::vector<CControlListener *> fListeners;
};

class CControlListener
{
public:
	virtual ~CControlListener() {}

	virtual void controlValueChanged(CControl &, double /*value*/) {};
	virtual void controlTriggered(CControl &) {};
};
