# Planning out the DOM based GUI system

## Idea

So it's like HTML where everything has sub-elements in a tree-structure
But obviously it's its own thing

I think I like how Godot does their GUI system more or less, with various frames that have different effects
Although I think I'll add optional names to elements

## Widgets

All widgets start with a base class, and users can define there own as well.

I need a set of various events that can be handled by all widgets. There are some predefined widgets with builtin events, but like I said, users can make their own.

__Containers__

The easiest set of things to add is containers.

Some containers center all elements, laying them on top of each other:
* Scrollable adds automatic scroll bars, and it has an option for turning off vertical or horizontal scroll bars, and those can be true/false or a variable
    * Note that a variable is indicated with $ plus an identifier
* Margin adds margins. It has an option for top, bottom, left, and right margins. These values can be pixels (ints) or variables
* Base container. Just holds things. Every window starts with a base container

These elements have "order" which can be set using sendToBack(int) and bringToFront(int)

Some containers are for arranging elements:
* horizontal box which has separation
* vertical box which has separation

The combinations of all these grids can achieve a similar effect to modern GUI systems

__Basic Types__

The basic types that exist though will be:
* Buttons which have string content, references to on-click function, and colors
* ImageButtons which are like buttons, but instead of color attributes, they have image things
* ColorRects with a color option that fills a container to act as backgrounds
* ImageRects are like ColorRects, but with images instead of colors
* TextFields which have a typing system, a flag to flip multiline or single-line, and various theme/text options
* Labels which are multiline with strings, and various theme options

## Concurrency

I'd like these to be semi-efficient, so using concurrency would be nice.
I'm not sure how to structure this from an architecture standpoint, so I need to do research

I think I can do drawing stuff and event handling in one thread, while event detection happens in another thread.
So maybe a growable array or whatever Go has which stores what actions to do next, and that gets appended on event triggers
