//#include "graphics/fade_tilemap.h"
//#include <SFML/Graphics.hpp>
//
//void FadeTilemap::applyFadeEffect(sf::RenderTarget& target)
//{
//    sf::View view = target.getView();
//    sf::Vector2f viewCenter = view.getCenter();
//    sf::FloatRect viewBounds(
//        viewCenter - view.getSize() / 2.f,
//        view.getSize()
//    );
//
//    float maxDistance = std::max(viewBounds.width, viewBounds.height) / 2.f;
//
//    for (auto& tile : tiles_)
//    {
//        sf::FloatRect tileBounds(
//            tile.Position().x,
//            tile.Position().y,
//            static_cast<float>(playground_tile_size_u_.x),
//            static_cast<float>(playground_tile_size_u_.y)
//        );
//
//        if (viewBounds.intersects(tileBounds))
//        {
//            float distance = std::hypot(tile.Position().x - viewCenter.x, tile.Position().y - viewCenter.y);
//            float fadeFactor = std::clamp(1.0f - (distance / maxDistance), 0.0f, 1.0f);
//            sf::Color color = sf::Color(255 * fadeFactor, 255 * fadeFactor, 255 * fadeFactor);
//            tile.setColor(color);
//        }
//    }
//}
//
//void FadeTilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//    const_cast<FadeTilemap*>(this)->applyFadeEffect(target);
//
//    for (const auto& tile : tiles_)
//    {
//        target.draw(tile, states);
//    }
//}
