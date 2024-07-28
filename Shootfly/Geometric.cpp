

#include "Geometric.h"

void Gemometric::RenderRectange(const GeoFormat& geo_data, SDL_Renderer* screen)
{
    SDL_SetRenderDrawColor(screen, geo_data.color_.r, geo_data.color_.g, geo_data.color_.b, 0xFF);
    SDL_RenderFillRect(screen, &geo_data.rect_);
}

void Gemometric::RenderOutline(const GeoFormat& geo_data, SDL_Renderer* screen)
{
    SDL_SetRenderDrawColor(screen, geo_data.color_.r, geo_data.color_.g, geo_data.color_.b, 0xFF);
    SDL_RenderDrawRect(screen, &geo_data.rect_);
}