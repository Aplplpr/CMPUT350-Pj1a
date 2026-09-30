#include "DrawContext.h"

namespace CMPUT350 {

/**
 * @brief Creates a drawing context for rendering to a window.
 *
 * @param window Shared pointer to the SFML render window.
 * @param font Shared pointer to the font used for text rendering.
 *
 * AI-generated documentation.
 */
DrawContext::DrawContext(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font)
    : mWindow(window), mFont(font) {}

/**
 * @brief Draws text centered at the given position.
 *
 * @param text The text to draw.
 * @param pixelSize The character size in pixels.
 * @param p The position that should be the center of the text.
 * @param c The text color.
 *
 * AI-generated documentation.
 */
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

/**
 * @brief Draws text starting at the given position.
 *
 * @param text The text to draw.
 * @param pixelSize The character size in pixels.
 * @param p The position of the text.
 * @param c The text color.
 *
 * AI-generated documentation.
 */
void DrawContext::DrawText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {
    sf::Text drawable(*mFont, text, pixelSize);
    drawable.setFillColor(sf::Color(c.r, c.g, c.b));
    drawable.setPosition({p.x, p.y});
    mWindow->draw(drawable);
}

/**
 * @brief Draws a filled circle centered at the given point.
 *
 * @param p The center position of the circle.
 * @param radius The circle radius in pixels.
 * @param c The fill color of the circle.
 *
 * AI-generated documentation.
 */
void DrawContext::DrawCircle(Point2D p, float radius, RGBColor c) {
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(c.r, c.g, c.b));
    circle.setPosition({p.x - radius, p.y - radius}); //top left corner
    mWindow->draw(circle);
}

/**
 * @brief Draws a filled rectangle.
 *
 * @param r The rectangle position and size.
 * @param c The fill color of the rectangle.
 *
 * AI-generated documentation.
 */
void DrawContext::DrawRect(Rect r, RGBColor c) {
    sf::RectangleShape rect(sf::Vector2f(r.width, r.height));
    rect.setPosition({r.topLeft.x, r.topLeft.y});
    rect.setFillColor(sf::Color(c.r, c.g, c.b));
    mWindow->draw(rect);
}

/**
 * @brief Draws the outline of a rectangle without filling its interior.
 *
 * @param r The rectangle position and size.
 * @param width The thickness of the outline in pixels.
 * @param c The outline color.
 *
 * AI-generated documentation.
 */
void DrawContext::FrameRect(Rect r, float width, RGBColor c) {
    sf::RectangleShape rect(sf::Vector2f(r.width, r.height));
    rect.setPosition({r.topLeft.x, r.topLeft.y});
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color(c.r, c.g, c.b));
    rect.setOutlineThickness(width);
    mWindow->draw(rect);
}

/**
 * @brief Draws a line segment with a specified width and color.
 *
 * @param from The starting point of the line.
 * @param to The ending point of the line.
 * @param width The width of the line in pixels.
 * @param c The line color.
 *
 * The line is represented by a four-point convex shape. A perpendicular
 * offset is calculated from the line direction so the shape can support
 * horizontal, vertical, and angled lines.
 *
 * AI-generated documentation.
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
