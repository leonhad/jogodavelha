bin_PROGRAMS = jogodavelha

jogodavelha_SOURCES = \
    game.cpp \
    graphics.cpp \
    main.cpp

jogodavelha_LDADD = $(GL_LIBS) $(SDL_LIBS)

noinst_HEADERS = \
    game.h \
    graphics.h

AM_CPPFLAGS = $(GL_CFLAGS) $(SDL_CFLAGS)
