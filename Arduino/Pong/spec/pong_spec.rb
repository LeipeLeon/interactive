class Pong

  attr :matrix
  attr :lr
  attr :rl

  def initialize
    setup_matrix
    @matrix[4][4] = 1
  end

  def tick
    find_a_way
  end

  def left_bar
    
  end

  def right_bar
    
  end

  def print_matrix
    @matrix.collect { |row|
      row.collect { |cols|
        cols == 0 ? '.' : 'X'
      }.join('')
    }.join("\n")
  end

  def find_a_way
    rand(3).to_i.-1
  end

private

  def setup_matrix
    @matrix = []
    (0..7).each do |x|
      @matrix[x] = []
      (0..7).each do |y|
        @matrix[x][y] = 0
      end
    end
  end

end

describe Pong do

  it "initiates a matrix of 8x8" do
    subject.matrix.length.should eql(8)
  end

  it "starts in the center" do
    subject.matrix[4][4].should eql(1)
  end

  it "has a bar on the left" do
    subject.matrix[1][4].should eql(1)
    subject.matrix[1][5].should eql(1)
  end

  it "prints matrix" do
    subject.print_matrix.should eql("........
........
........
........
....X...
........
........
........")
  end

  it "starts and goes to the left" do
    subject.tick
    subject.should_receive(:find_a_way).and_return(0)
    subject.print_matrix.should eql("........
........
........
........
...X....
........
........
........")
  end

  it "should find the next step" do
    subject.find_a_way.should < 2
    subject.find_a_way.should > -2
  end

end
