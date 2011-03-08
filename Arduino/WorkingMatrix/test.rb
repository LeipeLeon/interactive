
BITMAP_SMILE = [
  0b00000000,
  0b11000011,
  0b11000011,
  0b00000000,
  0b00011000,
  0b00011000,
  0b11000011,
  0b00111100
]

BITMAP_L = [
  0b00000000,
  0b11000000,
  0b11000000,
  0b11000000,
  0b11000000,
  0b11111110,
  0b00000000,
  0b00000000
]

BITMAP_H = [
  0b00000000,
  0b11000110,
  0b11000110,
  0b11111110,
  0b11000110,
  0b11000110,
  0b00000000,
  0b00000000
]

BITMAP_E = [
  0b00000000,
  0b11111110,
  0b11000000,
  0b11110000,
  0b11000000,
  0b11111110,
  0b00000000,
  0b00000000
]

BITMAP_O = [
  0b00000000,
  0b11111110,
  0b11000110,
  0b11000110,
  0b11000110,
  0b11111110,
  0b00000000,
  0b00000000
]

BITMAP_SPACE = [
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000
]


def display_bitMap(map)
  (0..7).each do |x|
    data = map[x]
    # puts data.to_i
    7.downto(0).each do |y|
      if (data & (1<<y)) > 0
        print "X"
      else
        print "."
      end
    end
    puts ""
  end
end

display_bitMap(BITMAP_H)
# display_bitMap(BITMAP_E)
# display_bitMap(BITMAP_L)
# display_bitMap(BITMAP_L)
# display_bitMap(BITMAP_O)
# display_bitMap(BITMAP_SMILE)
# display_bitMap(BITMAP_SPACE)





