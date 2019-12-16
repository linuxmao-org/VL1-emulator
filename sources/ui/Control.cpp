#include "Control.h"

void CControl::setValue(double value)
{
	if (fValue == value)
		return;

	fValue = value;

	for (CControlListener *cl : fListeners)
		cl->controlValueChanged(*this);

	repaint();
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
