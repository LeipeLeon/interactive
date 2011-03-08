
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

@pixels = [
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000,
  0b0000000000000000
]


def display_bitMap(map)
  7.downto(0).each do |s|
    (0..7).each do |r| # row
      @pixels[r] = @pixels[r] << 1
      data = map[r]
      if (data & (1<<s)) > 0
        @pixels[r] = @pixels[r] ^ 1
      end
      15.downto(0).each do |y|
        if (@pixels[r] & (1<<y)) > 0
          print "X"
        else
          print "."
        end
      end
      puts ""
    end
  end
end

display_bitMap(BITMAP_H)
display_bitMap(BITMAP_E)
display_bitMap(BITMAP_L)
display_bitMap(BITMAP_L)
display_bitMap(BITMAP_O)
display_bitMap(BITMAP_SMILE)
display_bitMap(BITMAP_SPACE)





