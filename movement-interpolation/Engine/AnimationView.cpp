#include "AnimationView.h"

void AnimationView::Render()
{
	gameObject->Render(model->current, 1.0f);
	gameObject->Render(model->start, 0.7f);
	gameObject->Render(model->end, 0.7f);

	for (size_t i = 0; i < model->intermediate.size(); i++)
	{
		gameObject->Render(model->intermediate[i], 0.4f);
	}
}
