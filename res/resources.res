SPRITE  ship    "gfx/player.png"        3   4   FAST    2
SPRITE  pl_expl "gfx/pl_explosion.png"  3   4   FAST    4
SPRITE  peashtr "gfx/bullet2.png"       1   3   FAST    0
SPRITE  astroid "gfx/asteroid.png"      2   2   FAST    0
SPRITE  enemy1  "gfx/enemy1.png"        2   2   FAST    2
SPRITE  enemy2  "gfx/enemy2.png"        3   3   FAST    4
SPRITE  en_bllt "gfx/en_bullet.png"     1   1   FAST    0
SPRITE  en_beam "gfx/en_beam.png"       1   4   FAST    0
SPRITE  explos  "gfx/explosion.png"     2   2   FAST    1
IMAGE   bckgrnd "tiles/space.png"       FAST
IMAGE   beam    "tiles/beam.png"        FAST
TILESET level_tileset "tiles/map.png" BEST
MAP level_map "tiles/map.png" level_tileset BEST
PALETTE palette_all "tiles/map.png"
TILESET cloud_tileset "tiles/mapc.png" BEST
MAP cloud_map "tiles/mapc.png" cloud_tileset BEST

IMAGE   boss1   "img/boss1.png"         FAST
