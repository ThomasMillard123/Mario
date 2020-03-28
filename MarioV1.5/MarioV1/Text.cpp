#include "Text.h"

Text::Text(SDL_Renderer* renderer,Texture2D* texture) {
	
	mRenderer=renderer;
	mTexture = texture;
	
	

}

void Text::Update() {

}
void Text::EnterText(std::string& Text, SDL_Event e) {
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			Text += "a";
			break;
		case SDLK_b:
			Text += "b";
			break;
		case SDLK_c:
			Text += "c";
			break;
		case SDLK_d:
			Text += "d";
			break;
		case SDLK_e:
			Text += "e";
			break;
		case SDLK_f:
			Text += "f";
			break;
		case SDLK_g:
			Text += "g";
			break;
		case SDLK_h:
			Text += "h";
			break;
		case SDLK_i:
			Text += "i";
			break;
		case SDLK_j:
			Text += "j";
			break;
		case SDLK_k:
			Text += "k";
			break;
		case SDLK_l:
			Text += "l";
			break;
		case SDLK_m:
			Text += "m";
			break;
		case SDLK_n:
			Text += "n";
			break;
		case SDLK_o:
			Text += "o";
			break;
		case SDLK_p:
			Text += "p";
			break;
		case SDLK_q:
			Text += "q";
			break;
		case SDLK_r:
			Text += "r";
			break;
		case SDLK_s:
			Text += "s";
			break;
		case SDLK_t:
			Text += "t";
			break;
		case SDLK_u:
			Text += "u";
			break;
		case SDLK_v:
			Text += "v";
			break;
		case SDLK_w:
			Text += "w";
			break;
		case SDLK_x:
			Text += "x";
			break;
		case SDLK_y:
			Text += "y";
			break;
		case SDLK_z:
			Text += "z";
			break;
		default:
			std::cerr << "invalied input" << std::endl;
			break;
		}
		break;
	default:
		break;
	}
}
void Text::Render(std::string text, Vector2D position) {
	mPosition = position;
	mText = text;
	for (int i=0; i < mText.length(); i++) {
		mSingleSpriteWidth = mTexture->GetWidth() / 48;
		mSingleSpriteHight = mTexture->GetHeight() / 31;
		mYPosition = mSingleSpriteHight * 8;
		//numbers
		if (mText[i] == '1') {
			mXPosition = mSingleSpriteWidth * 2.2;
			
		}
		else if (mText[i] == '2') {
			mXPosition = mSingleSpriteWidth * 3.0;
			
		}
		else if (mText[i] == '3') {
			mXPosition = mSingleSpriteWidth * 4.0;
			
		}
		else if (mText[i] == '4') {
			mXPosition = mSingleSpriteWidth * 5.0;
			
		}
		else if (mText[i] == '5') {
			mXPosition = mSingleSpriteWidth * 6.0;
			
		}
		else if (mText[i] == '6') {
			mXPosition = mSingleSpriteWidth * 7.0;
			
		}
		else if (mText[i] == '7') {
			mXPosition = mSingleSpriteWidth * 8.0;
			
		}
		else if (mText[i] == '8') {
			mXPosition = mSingleSpriteWidth * 9.0;
			
		}
		else if (mText[i] == '9') {
			mXPosition = mSingleSpriteWidth * 10.0;
			
		}
		else if(mText[i]=='0')
		{
			mXPosition = mSingleSpriteWidth * 1.4;
			
		}
		//text
		else if (mText[i] == 'a' || mText[i] == 'A') {
			mSingleSpriteWidth = mTexture->GetWidth() / 70;
			mXPosition = mSingleSpriteWidth * 18.6f;
		}
		else if (mText[i] == 'b' || mText[i] == 'B') {
			mSingleSpriteWidth = mTexture->GetWidth() / 70;
			mXPosition = mSingleSpriteWidth * 19.8f;
		}
		else if (mText[i] == 'c' || mText[i] == 'C') {
			mSingleSpriteWidth = mTexture->GetWidth() / 70;
			mXPosition = mSingleSpriteWidth * 20.7f;
		}
		else if (mText[i] == 'd' || mText[i] == 'D') {
			mSingleSpriteWidth = mTexture->GetWidth() / 70;
			mXPosition = mSingleSpriteWidth * 22.0f;
		}
		else if (mText[i] == 'e' || mText[i] == 'E') {
			mSingleSpriteWidth = mTexture->GetWidth() / 70;
			mXPosition = mSingleSpriteWidth * 23.0f;
		}
		else if (mText[i] == 'f' || mText[i] == 'F') {
			mSingleSpriteWidth = mTexture->GetWidth() / 70;
			mXPosition = mSingleSpriteWidth * 24.0f;
		}
		else if (mText[i] == 'g' || mText[i] == 'G') {
			mXPosition = mSingleSpriteWidth * 16.7f;
		}
		else if (mText[i] == 'h' || mText[i] == 'H') {
			mSingleSpriteWidth = mTexture->GetWidth() / 70;
			mXPosition = mSingleSpriteWidth * 26.5f;
		}
		else if (mText[i] == 'i' || mText[i] == 'I') {
			mSingleSpriteWidth = mTexture->GetWidth() / 90;
			mXPosition = mSingleSpriteWidth * 41.3;
		}
		else if (mText[i] == 'j' || mText[i] == 'J') {
			mSingleSpriteWidth = mTexture->GetWidth() / 60;
			mXPosition = mSingleSpriteWidth * 24.0;
		}
		else if (mText[i] == 'k' || mText[i] == 'K') {
			mSingleSpriteWidth = mTexture->GetWidth() / 60;
			mXPosition = mSingleSpriteWidth * 25.0;
		}
		else if (mText[i] == 'l' || mText[i] == 'L') {
			mSingleSpriteWidth = mTexture->GetWidth() / 70;
			mXPosition = mSingleSpriteWidth *30.3;
		}
		else if (mText[i] == 'm' || mText[i] == 'M') {

			mXPosition = mSingleSpriteWidth * 20.7;
		}
		else if (mText[i] == 'n' || mText[i] == 'N') {
			mSingleSpriteWidth = mTexture->GetWidth() / 60;
			mXPosition = mSingleSpriteWidth * 28.1;
		}
		else if (mText[i] == 'o' || mText[i] == 'O') {
			mXPosition = mSingleSpriteWidth * 22.5;
		}
		else if (mText[i] == 'p' || mText[i] == 'P') {
			mSingleSpriteWidth = mTexture->GetWidth() / 60;
			mXPosition = mSingleSpriteWidth * 30.4;
		}
		else if (mText[i] == 'q' || mText[i] == 'Q') {

			mXPosition = mSingleSpriteWidth * 24.3;
		}
		else if (mText[i] == 'r' || mText[i] == 'R') {
			mSingleSpriteWidth = mTexture->GetWidth() / 60;
			mXPosition = mSingleSpriteWidth * 32.5;
		}
		else if (mText[i] == 's' || mText[i] == 'S') {
			mSingleSpriteWidth = mTexture->GetWidth() / 60;
			mXPosition = mSingleSpriteWidth * 33.5;
		}
		else if (mText[i] == 't' || mText[i] == 'T') {
			mSingleSpriteWidth = mTexture->GetWidth() / 60;
			mXPosition = mSingleSpriteWidth * 34.5;
		}
		else if (mText[i] == 'u' || mText[i] == 'U') {
		mSingleSpriteWidth = mTexture->GetWidth() / 60;
			mXPosition = mSingleSpriteWidth * 35.5;
		}
		else if (mText[i] == 'v' || mText[i] == 'V') {
		mSingleSpriteWidth = mTexture->GetWidth() / 60;
			mXPosition = mSingleSpriteWidth * 36.5;
		}
		else if (mText[i] == 'w' || mText[i] == 'W') {
		mSingleSpriteWidth = mTexture->GetWidth() / 40;
			mXPosition = mSingleSpriteWidth * 26.3;
		}
		else if (mText[i] == 'x' || mText[i] == 'X') {
		mSingleSpriteWidth = mTexture->GetWidth() / 60;
			mXPosition = mSingleSpriteWidth * 39.0;
		}
		else if (mText[i] == 'y' || mText[i] == 'Y') {
		mSingleSpriteWidth = mTexture->GetWidth() / 60;
			mXPosition = mSingleSpriteWidth * 40.0;
		}
		else if (mText[i] == 'z' || mText[i] == 'Z') {
			mXPosition = mSingleSpriteWidth * 32.0;

		}
		else {
		mXPosition = mSingleSpriteWidth * 0;
		}

		portionOfSpritesheet = { mXPosition,mYPosition,mSingleSpriteWidth,mSingleSpriteHight };
		destRect = { (int)mPosition.x,(int)mPosition.y,(int)mSingleSpriteWidth,(int)mSingleSpriteHight };
		mTexture->RenderSpritesheet(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
		mPosition.x += mSingleSpriteWidth;
	}
}

Text::~Text() {
	delete mTexture;
	mTexture = NULL;

	mRenderer = NULL;
}