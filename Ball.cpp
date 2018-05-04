#include "Ball.h"

Ball::Ball()
{
    p_centre.x = 0;
    p_centre.y = 0;
    radius = 0;
    CalculateAngles();
}

Ball::~Ball()
{
#ifdef DEBUG_MESSAGES_SHOW
    std::cout << "Ball end\n";
#endif // DEBUG_MESSAGES_SHOW
}

void Ball::CalculateAngles()
{
    for(int i=0; i<360; i++)
    {
        CosForAngles.push_back(cos(i*PI_by_180));
        SinForAngles.push_back(sin(i*PI_by_180));
    }
}

void Ball::setCentreXY(int x, int y)
{
    // x и y должны быть неотрицательны
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    p_centre.x = x;
    p_centre.y = y;
}

void Ball::setRadius(int r)
{
    // Радиус должен быть неотрицательным
    if(r < 0)
        r = 0;
    radius = r;
}

int Ball::getRadius()
{
    return radius;
}

void Ball::draw(SDL_Renderer *renderer)
{
    drawCircle(renderer);
    fillCircle(renderer);
}

void Ball::drawCircle(SDL_Renderer* renderer)
{
	double error = (double)-radius;
	double x = (double)radius - 0.5;
	double y = (double)0.5;
	double cx = p_centre.x - 0.5;
	double cy = p_centre.y - 0.5;

	while (x >= y)
	{
		SDL_RenderDrawPoint(renderer, (int)(cx + x), (int)(cy + y));
		SDL_RenderDrawPoint(renderer, (int)(cx + y), (int)(cy + x));

		if (x != 0)
		{
			SDL_RenderDrawPoint(renderer, (int)(cx - x), (int)(cy + y));
			SDL_RenderDrawPoint(renderer, (int)(cx + y), (int)(cy - x));
		}

		if (y != 0)
		{
			SDL_RenderDrawPoint(renderer, (int)(cx + x), (int)(cy - y));
			SDL_RenderDrawPoint(renderer, (int)(cx - y), (int)(cy + x));
		}

		if (x != 0 && y != 0)
		{
			SDL_RenderDrawPoint(renderer, (int)(cx - x), (int)(cy - y));
			SDL_RenderDrawPoint(renderer, (int)(cx - y), (int)(cy - x));
		}

		error += y;
		++y;
		error += y;

		if (error >= 0)
		{
			--x;
			error -= x;
			error -= x;
		}
    }
}

void Ball::fillCircle (SDL_Renderer* renderer)
{
    int cx = p_centre.x;
    int cy = p_centre.y;
	for (double dy = 1; dy <= radius; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		SDL_RenderDrawLine(renderer, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
		SDL_RenderDrawLine(renderer, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
    }
}

SDL_Rect Ball::getRectArea()
{
    // Вычисляем область текущего
    // расположения объекта
    SDL_Rect ball_rect;
    ball_rect.x = p_centre.x - radius;
    ball_rect.y = p_centre.y - radius;
    // +1, чтобы не оставалось следов от шарика
    ball_rect.h = radius * 2 + 1;
    ball_rect.w = radius * 2 + 1;
    return ball_rect;
}


Ball::BallBound Ball::getBallBound() const
{
	BallBound bb;
	bb.l = p_centre.x - radius;
	bb.r = p_centre.x + radius;
	bb.t = p_centre.y - radius;
	bb.b = p_centre.y + radius;
	return bb;
}
