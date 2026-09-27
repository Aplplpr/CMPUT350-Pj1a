#include "DrawContext.h"

namespace CMPUT350 {

DrawContext::DrawContext(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font)
    : mWindow(window), mFont(font) {}

void DrawContext::DrawCenteredText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {
    sf::Text drawable(*mFont, text, pixelSize);
    drawable.setFillColor(sf::Color(c.r, c.g, c.b));

    sf::FloatRect bounds = drawable.getLocalBounds();

    drawable.setOrigin({
        bounds.position.x + bounds.size.x / 2.0f,
        bounds.position.y + bounds.size.y / 2.0f
    });

    drawable.setPosition({p.x, p.y});

    mWindow->draw(drawable);
}

void DrawContext::DrawText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {
    sf::Text drawable(*mFont, text, pixelSize);
    drawable.setFillColor(sf::Color(c.r, c.g, c.b));
    drawable.setPosition({p.x, p.y});
    mWindow->draw(drawable);
}

void DrawContext::DrawCircle(Point2D p, float radius, RGBColor c) {
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(c.r, c.g, c.b));
    circle.setPosition({p.x - radius, p.y - radius}); //top left corner
    mWindow->draw(circle);
}

void DrawContext::DrawRect(Rect r, RGBColor c) {
    sf::RectangleShape rect(sf::Vector2f(r.width, r.height));
    rect.setPosition({r.topLeft.x, r.topLeft.y});
    rect.setFillColor(sf::Color(c.r, c.g, c.b));
    mWindow->draw(rect);
}

void DrawContext::FrameRect(Rect r, float width, RGBColor c) {
    sf::RectangleShape rect(sf::Vector2f(r.width, r.height));
    rect.setPosition({r.topLeft.x, r.topLeft.y});
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color(c.r, c.g, c.b));
    rect.setOutlineThickness(width);
    mWindow->draw(rect);
}

/**
 * @brief Draws a line between two points with a specified width and color.
 *
 * @param from The starting point of the line (Point2D).
 * @param to The ending point of the line (Point2D).
 * @param width The width of the line in pixels.
 * @param c The color of the line, specified as an RGBColor object.
 *
 * This function calculates the distance and angle between the two points
 * and uses a polygone shape to represent the line. The line is drawn
 * relative to the world offset and rendered onto the associated window.
 */
void DrawContext::DrawLine(Point2D from, Point2D to, float width, RGBColor c) {
    float dx = to.x - from.x;
    float dy = to.y - from.y;

    float length = std::sqrt(dx * dx + dy * dy);

    if (length == 0) {
        return;
    }

    float halfWidth = width / 2.0f;

    float nx = -dy / length * halfWidth;
    float ny =  dx / length * halfWidth;

    sf::ConvexShape line;
    line.setPointCount(4);

    line.setPoint(0, {from.x + nx, from.y + ny});
    line.setPoint(1, {to.x + nx,   to.y + ny});
    line.setPoint(2, {to.x - nx,   to.y - ny});
    line.setPoint(3, {from.x - nx, from.y - ny});

    line.setFillColor(sf::Color(c.r, c.g, c.b));

    mWindow->draw(line);
}

int DrawContext::GetWindowWidth() { return mWindow->getSize().x; }

int DrawContext::GetWindowHeight() { return mWindow->getSize().y; }

}  // namespace CMPUT350
