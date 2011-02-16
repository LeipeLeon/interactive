class slider {
  int xpos, ypos, thesize, p, previous_size;
  boolean slide;
  boolean toggled = true;
  color c, cb;

  // initializer
  slider (int x, int y, int s, color col) {
    xpos    = x;
    ypos    = y;
    thesize = s;
    p       = 0;
    slide   = true;
    c       = col;
    cb      = color(red(c),green(c),blue(c),150);
  }

  int toggle() {
    println("POS:" + p);
    println("POSPREV:" + previous_size);
    if (toggled) {
      previous_size = p ;
      p = 0;
    } else {
      p = previous_size;
    }
    toggled = ! toggled ;
    return p*2;
  }

  void setP(int newP) {
    p = newP;
    previous_size = newP ;
    toggled = true;
  }

  void render() {
    println("POS:" + p);
    stroke(40);
    strokeWeight(10);
    noFill();
    line(xpos,ypos,xpos,ypos+thesize);

    stroke(80);
    strokeWeight(2);
    noFill();
    line(xpos,ypos,xpos,ypos+thesize);

    noStroke();
    fill(cb);
    ellipse(xpos, thesize-p+ypos, 17, 17);
    fill(c);
    ellipse(xpos, thesize-p+ypos, 13, 13);

    //text(thesize-dialy,xpos+10,dialy+ypos+5);

    // replace the +'s with double ampersands (web display issues)
    if (slide = true && mousePressed==true && mouseX<xpos+15 && mouseX>xpos-15){
      if ((mouseY<=ypos+thesize+10) && (mouseY>=ypos-10)) {
        p=(3*p+(thesize-(mouseY-ypos)))/4;
        if (p<0) {
          p=0;
        } else if (p>thesize) {
          p=thesize;
        }
      }
    }
  }
}
