#ifndef ANIMATIONPERSONNAGE_H
#define ANIMATIONPERSONNAGE_H

#include "Framework/GlWindow.h"


class AnimationPersonnage : public GlWindow
{
	public:
        AnimationPersonnage();
        ~AnimationPersonnage();

		/*!
		*\brief Initialization des objets.
		*/
		bool initializeObjects();

		/*!
		*\brief Rendu de la scène.
		*/
        void updateAnimation(float fDeltaTime);
		void render();

		void keyPressEvent(QKeyEvent *);

        void mouseMoveEvent(QMouseEvent *event);

        void mousePressEvent(QMouseEvent *event);
};


#endif
