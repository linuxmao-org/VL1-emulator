#include "Control.h"

void CControl::reportValueChanged(double value)
{
	for (CControlListener *cl : fListeners)
		cl->controlValueChanged(*this, value);
}

void CControl::reportTriggered()
{
	for (CControlListener *cl : fListeners)
		cl->controlTriggered(*this);
}

void CControl::addListener(CControlListener *cl)
{
	DISTRHO_SAFE_ASSERT_RETURN(cl != nullptr, );

	fListeners.push_back(cl);
}

void CControl::removeListener(CControlListener *cl)
{
	auto it = std::find(fListeners.begin(), fListeners.end(), cl);

	DISTRHO_SAFE_ASSERT_RETURN(it != fListeners.end(), );

	fListeners.erase(it);
}
