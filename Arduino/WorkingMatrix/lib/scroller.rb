
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


class Scroller

  attr :pixels
  attr_writer :pixels

  def initialize
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
  end

  def compose_row(row)
    15.downto(0).collect do |y|
      if ( @pixels[row] & ( 1 << y )) > 0
        "X"
      else
        "."
      end
    end
  end

  def display_bitMapLeft(map)
    7.downto(0).each do |offset|
      puts shift_buffer_left(map, offset)
    end
  end

  def display_bitMapDown(map)
    7.downto(0).each do |offset|
      puts shift_buffer_down(map, offset)
    end
  end

  def shift_buffer_left(map, offset)
    (0..7).collect do |r| # row
      @pixels[r] = @pixels[r] << 1
      if (map[r] & (1 << offset )) > 0
        @pixels[r] = @pixels[r] ^ 1
      end
      compose_row(r).join('')
    end
  end

  def shift_buffer_down(map, offset)
    ret = 6.downto(0).collect do |r| # row
      @pixels[r+1] = @pixels[r]
      # if (map[r] & (1 << offset )) > 0
      #   @pixels[r] = @pixels[r] ^ 1
      # end
      compose_row(r).join('')
    end
    @pixels[0] = map[7-offset]
    ret << compose_row(0).join('')
  end

end

