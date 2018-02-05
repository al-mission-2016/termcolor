//!
//! style
//! ~~~~~
//!
//! "Style" extends termcolor library by adding support of styles, i.e.
//! objects that keep color/attribute info. User can create several such
//! style-objects to quickly change current ostream state.
//!
//! "Style" is platform agnostic and depends only on "termcolor.hpp".
//!
//! Example.
//!   style st1, st2;
//!   st1.red().bold();
//!   st2.blue().on_white().underline();
//!   cout << st1 << "Cosmos " << st2 << "is wonderful" << reset << endl;
//!
//! :copyright: (c) 2017 by Alexei Mission
//! :license: BSD, see LICENSE for details
//! :v0.2

#ifndef STYLE_HPP
#define STYLE_HPP

#include <termcolor/termcolor.hpp>

namespace termcolor
{
    //! Style is a set of compatible attributes that can be applied
    //! to the ostream updating current state.
    class style
    {
        struct color_rgb_24bit
        {
            uint8_t foreground_red, foreground_green, foreground_blue;
            uint8_t background_red, background_green, background_blue;
            void clear()
            {
                foreground_red = foreground_green = foreground_blue = 0;
                background_red = background_green = background_blue = 0;
            }
        };

        struct color_index_8bit
        {
            uint8_t foreground;
            uint8_t background;
        };

        struct color_named_4bit
        {
            uint8_t foreground;
            uint8_t background;
        };

        union colors_tag
        {
            color_named_4bit    named;
            color_index_8bit    index;
            color_rgb_24bit     rgb;
        };

        enum color_type
        {   color_type_none
        ,   color_type_named
        ,   color_type_indexed
        ,   color_type_rgb
        };

        enum color_name
        {   color_grey
        ,   color_red
        ,   color_green
        ,   color_yellow
        ,   color_blue
        ,   color_magenta
        ,   color_cyan
        ,   color_white
        };

    private:
        colors_tag  _colors;
        uint16_t    _foreground_type: 2;
        uint16_t    _background_type: 2;
        uint16_t    _reset          : 1;
        uint16_t    _bold           : 1;
        uint16_t    _dark           : 1;
        uint16_t    _underline      : 1;
        uint16_t    _blink          : 1;
        uint16_t    _reverse        : 1;
        uint16_t    _concealed      : 1;
        uint16_t    __reserved      : 5;

    public:
        style()
        {
            _colors.rgb.clear();
            _foreground_type = color_type_none;
            _background_type = color_type_none;
            _reset           = 1;
            _bold            = 0;
            _dark            = 0;
            _underline       = 0;
            _blink           = 0;
            _reverse         = 0;
            _concealed       = 0;
            __reserved       = 0;
        }

#       if (__cplusplus >= 201100)
        style( style const& ) = default;
        style& operator= ( style const& ) = default;
#       endif

    friend std::ostream& operator<< (std::ostream& stream, style);

    public:
        style& reset    ( bool o = true ) { _reset     = o ? 1 : 0; return *this; }
        style& bold     ( bool o = true ) { _bold      = o ? 1 : 0; return *this; }
        style& dark     ( bool o = true ) { _dark      = o ? 1 : 0; return *this; }
        style& underline( bool o = true ) { _underline = o ? 1 : 0; return *this; }
        style& blink    ( bool o = true ) { _blink     = o ? 1 : 0; return *this; }
        style& reverse  ( bool o = true ) { _reverse   = o ? 1 : 0; return *this; }
        style& concealed( bool o = true ) { _concealed = o ? 1 : 0; return *this; }

    public:
        style& grey   () { _colors.named.foreground = color_grey    ; _foreground_type = color_type_named; return *this; }
        style& red    () { _colors.named.foreground = color_red     ; _foreground_type = color_type_named; return *this; }
        style& green  () { _colors.named.foreground = color_green   ; _foreground_type = color_type_named; return *this; }
        style& yellow () { _colors.named.foreground = color_yellow  ; _foreground_type = color_type_named; return *this; }
        style& blue   () { _colors.named.foreground = color_blue    ; _foreground_type = color_type_named; return *this; }
        style& magenta() { _colors.named.foreground = color_magenta ; _foreground_type = color_type_named; return *this; }
        style& cyan   () { _colors.named.foreground = color_cyan    ; _foreground_type = color_type_named; return *this; }
        style& white  () { _colors.named.foreground = color_white   ; _foreground_type = color_type_named; return *this; }

        style& on_grey   () { _colors.named.background = color_grey    ; _background_type = color_type_named; return *this; }
        style& on_red    () { _colors.named.background = color_red     ; _background_type = color_type_named; return *this; }
        style& on_green  () { _colors.named.background = color_green   ; _background_type = color_type_named; return *this; }
        style& on_yellow () { _colors.named.background = color_yellow  ; _background_type = color_type_named; return *this; }
        style& on_blue   () { _colors.named.background = color_blue    ; _background_type = color_type_named; return *this; }
        style& on_magenta() { _colors.named.background = color_magenta ; _background_type = color_type_named; return *this; }
        style& on_cyan   () { _colors.named.background = color_cyan    ; _background_type = color_type_named; return *this; }
        style& on_white  () { _colors.named.background = color_white   ; _background_type = color_type_named; return *this; }

        style& color   ( uint8_t i ) { _colors.index.foreground = i; _foreground_type = color_type_indexed; return *this; }
        style& on_color( uint8_t i ) { _colors.index.background = i; _background_type = color_type_indexed; return *this; }

        style& color( uint8_t red_, uint8_t green_, uint8_t blue_ )
        {
            _colors.rgb.foreground_red   = red_  ;
            _colors.rgb.foreground_green = green_;
            _colors.rgb.foreground_blue  = blue_ ;
            _foreground_type = color_type_rgb;
            return *this;
        }

        style& on_color( uint8_t red_, uint8_t green_, uint8_t blue_ )
        {
            _colors.rgb.background_red   = red_  ;
            _colors.rgb.background_green = green_;
            _colors.rgb.background_blue  = blue_ ;
            _background_type = color_type_rgb;
            return *this;
        }
    };

    #if (__cplusplus >= 201100)
    static_assert( sizeof(style) == 8, "expected 8 bytes size" );
    #endif

    inline
    std::ostream& operator<< (std::ostream& stream, style style_)
    {
        if (style_._reset    ) stream << reset;
        if (style_._bold     ) stream << bold;
        if (style_._dark     ) stream << dark;
        if (style_._underline) stream << underline;
        if (style_._blink    ) stream << blink;
        if (style_._reverse  ) stream << reverse;
        if (style_._concealed) stream << concealed;

        switch (style_._foreground_type)
        {
            case style::color_type_named:
                switch ( style_._colors.named.foreground )
                {
                case style::color_grey    : stream << grey    ; break;
                case style::color_red     : stream << red     ; break;
                case style::color_green   : stream << green   ; break;
                case style::color_yellow  : stream << yellow  ; break;
                case style::color_blue    : stream << blue    ; break;
                case style::color_magenta : stream << magenta ; break;
                case style::color_cyan    : stream << cyan    ; break;
                case style::color_white   : stream << white   ; break;
                }
                break;
            case style::color_type_indexed:
                stream << color(style_._colors.index.foreground);
                break;
            case style::color_type_rgb:
                stream << color
                (   style_._colors.rgb.foreground_red
                ,   style_._colors.rgb.foreground_green
                ,   style_._colors.rgb.foreground_blue
                );
                break;
            default: break;
        }

        switch (style_._background_type)
        {
            case style::color_type_named:
                switch ( style_._colors.named.background )
                {
                case style::color_grey    : stream << on_grey    ; break;
                case style::color_red     : stream << on_red     ; break;
                case style::color_green   : stream << on_green   ; break;
                case style::color_yellow  : stream << on_yellow  ; break;
                case style::color_blue    : stream << on_blue    ; break;
                case style::color_magenta : stream << on_magenta ; break;
                case style::color_cyan    : stream << on_cyan    ; break;
                case style::color_white   : stream << on_white   ; break;
                }
                break;
            case style::color_type_indexed:
                stream << on_color(style_._colors.index.background);
                break;
            case style::color_type_rgb:
                stream << on_color
                (   style_._colors.rgb.background_red
                ,   style_._colors.rgb.background_green
                ,   style_._colors.rgb.background_blue
                );
                break;
            default: break;
        }

        return stream;
    }
}

#endif // STYLE_HPP
