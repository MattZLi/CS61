void io61_fill(io61_file* f) {
    // Fill the read cache with new data, starting from file offset `end_tag`.
    // Only called for read caches.

    // Check invariants.
    assert(f->tag <= f->pos_tag && f->pos_tag <= f->end_tag);
    assert(f->end_tag - f->pos_tag <= f->bufsize);

    // Reset the cache to empty.
    f->tag = f->pos_tag = f->end_tag;

    // Recheck invariants (good practice!).
    assert(f->tag <= f->pos_tag && f->pos_tag <= f->end_tag);
    assert(f->end_tag - f->pos_tag <= f->bufsize);
}

// Easy Read
ssize_t io61_read(io61_file* f, char* buf, size_t sz) {
    // Check invariants.
    assert(f->tag <= f->pos_tag && f->pos_tag <= f->end_tag);
    assert(f->end_tag - f->pos_tag <= f->bufsize);

    // The desired data is guaranteed to lie within this cache slot.
    assert(sz <= f->bufsize && f->pos_tag + sz <= f->end_tag);

    memcpy(buf, f->cbuf + f->pos_tag - f->tag, sz)
    f->pos_tag += sz
    return sz
}

// Full Read
ssize_t io61_read(io61_file* f, char* buf, size_t sz) {
    // Check invariants.
    assert(f->tag <= f->pos_tag && f->pos_tag <= f->end_tag);
    assert(f->end_tag - f->pos_tag <= f->bufsize);
    ssize_t nbytes = 0;
    while (nbytes < sz){
    	// Check to see if cache is valid
    	if (f->pos_tag == f->end_tag){
    		io61_fill(f);
    		// c-cache is cache buffer
    		// Read sz bytes while you can and then stop
    		// Break out of loop if nothing can be filled anymore
    		if (f->pos_tag == f->end_tag){
    			break;
    		}
    	}
    	else{
    		f->pos_tag = f->end_tag = 0;   // mark cache as empty
            ssize_t n = read(f->fd, f->buffer, f->bufsize);
            if (n > 0)
                f->end_tag = n;
            else
                return f->end_tag ? f->end_tag : n;
        }
    	buf[nbytes] = f->cbuf[f->pos_tag - f->tag];
    	nbytes++;
    	f->pos_tag++;
    }
    return nbytes
}

// Efficient Read
ssize_t io61_read(io61_file* f, char* buf, size_t sz) {
    // Check invariants.
    assert(f->tag <= f->pos_tag && f->pos_tag <= f->end_tag);
    assert(f->end_tag - f->pos_tag <= f->bufsize);
    ssize_t nbytes = 0;
    while (nbytes < sz){
    	// Check to see if cache is valid
    	if (f->pos_tag == f->end_tag){
    		io61_fill(f);
    		// c-cache is cache buffer
    		// Read sz bytes while you can and then stop
    		// Break out of loop if nothing can be filled anymore
    		if (f->pos_tag == f->end_tag){
    			break;
    		}
    	}
    	else{
    		f->pos_tag = f->end_tag = 0;   // mark cache as empty
            ssize_t n = read(f->fd, f->buffer, f->bufsize);
            if (n > 0)
                f->end_tag = n;
            else
                return f->end_tag ? f->end_tag : n;
        }
    	buf[nbytes] = f->cbuf[f->pos_tag - f->tag];
    	nbytes++;
    	f->pos_tag++;
    }
    return nbytes
}

// Read a character, seek, and then read a character.  Change tag values and then 
// A tag in the array, then reading backwards.  Read c and then seek backwards.
// Update tag values and then fill
// Make sure the caches always align
// If tag = 4096, 4096, 4095, then cache returns values successfully
// Seek to zero and loading up cache at 4095
// Always making sure cache is 4096

// Cache aligned to block size

// Buffer the writes, where the evidence from array stored in the cache
ssize_t io61_write(io61_file* f, const char* buf, size_t sz) {
    // Check invariants.
    assert(f->tag <= f->pos_tag && f->pos_tag <= f->end_tag);
    assert(f->end_tag - f->pos_tag <= f->bufsize);

    // Write cache invariant.
    assert(f->pos_tag == f->end_tag);

    // The desired data is guaranteed to fit within this cache slot.
    assert(sz <= f->bufsize && f->pos_tag + sz <= f->tag + f->bufsize);

    memcpy(f->buffer + f->pos_tag - f->tag, buf, sz){
    	f->pos_tag += sz
    	retirm sz;
    }

    f->cbuf[f->pos_tag - f_>tag] = buf[nbytes];
    nbytes++;
    f->pos_tag++;
}

// Easy write
// Buffer the writes, where the evidence from array stored in the cache
ssize_t io61_write(io61_file* f, const char* buf, size_t sz) {
    // Check invariants.
    assert(f->tag <= f->pos_tag && f->pos_tag <= f->end_tag);
    assert(f->end_tag - f->pos_tag <= f->bufsize);

    // Write cache invariant.
    assert(f->pos_tag == f->end_tag);

    // The desired data is guaranteed to fit within this cache slot.
    assert(sz <= f->bufsize && f->pos_tag + sz <= f->tag + f->bufsize);

    memcpy(f->buffer + f->pos_tag - f->tag, buf, sz){
    	f->pos_tag += sz;
    	return sz;
    }

    f->cbuf[f->pos_tag - f_>tag] = buf[nbytes];
    nbytes++;
    f->pos_tag++;
}

// Hard write
ssize_t io61_write(io61_file* f, const char* buf, size_t sz) {

    // Check invariants.
    assert(f->tag <= f->pos_tag && f->pos_tag <= f->end_tag);
    assert(f->end_tag - f->pos_tag <= f->bufsize);

    // Write cache invariant.
    assert(f->pos_tag == f->end_tag);

    // The desired data is guaranteed to fit within this cache slot.
    assert(sz <= f->bufsize && f->pos_tag + sz <= f->tag + f->bufsize);
    ssize_t nbytes = 0;
    while (nbytes < sz){
    	if (f->pos_tag - f->tag == f->cbufsize){
    		io61_flush(f);
    	}
    	f->cbuf[f->pos_tag - f->tag] = buf[nbytes];
    	nbytes++;
    	f->pos_tag++;
    }
    return nbytes;
}

// Efficient
ssize_t io61_write(io61_file* f, const char* buf, size_t sz) {

    // Check invariants.
    assert(f->tag <= f->pos_tag && f->pos_tag <= f->end_tag);
    assert(f->end_tag - f->pos_tag <= f->bufsize);

    // Write cache invariant.
    assert(f->pos_tag == f->end_tag);

    // The desired data is guaranteed to fit within this cache slot.
    assert(sz <= f->bufsize && f->pos_tag + sz <= f->tag + f->bufsize);
    ssize_t nbytes = 0;
    while (nbytes < sz){
    	if (f->pos_tag - f->tag == f->cbufsize){
    		io61_flush(f);
    	}
    	ssize_t n = sz - nbytes

    	if (n > f->bufsize - (f->pos_tag - f->tag)){
                n = f->bufsize - (f->pos_tag - f->tag);
        }

    	memcpy(f->cbuf[f->pos_tag - f->tag], &buf[nbytes], n);
    	nbytes += n;
    	f->pos_tag+=n;
    }
    io61_flush;
    return nbytes;
}

void io61_flush(io61_file* f) {
    // Check invariants.
    assert(f->tag <= f->pos_tag && f->pos_tag <= f->end_tag);
    assert(f->end_tag - f->pos_tag <= f->bufsize);

    // Write cache invariant.
    assert(f->pos_tag == f->end_tag);
    ssize_t n = write(f->fd, f->cbuf, f->pos_tag - f->tag);
    f->tag = f->pos_tag;
}

// Easy seek

int io61_seek(io61_file* f, off_t off) {
    if (off < f->tag || off > f->end_tag) {
        off_t r = lseek(f->fd, off, SEEK_SET);
        if (r != off)
            return -1;
        f->tag = f->end_tag = off;
    }
    f->pos_tag = off;
    return 0;
}

// Efficient seek
int io61_seek(io61_file* f, off_t off) {
    if (off >= f->tag && off <= f->end_tag) {
    	f->pos_tag = off;
    	return 0;
    }
    else{
    	off_t aligned_off = off - (off % BUFSIZ);
    	off_t r = lseek(f->fd, aligned_off, SEEK_SET);
    	if (r == aligned_off){
    		f->tag = f->end_tag = aligned_off;
    		f->pos_tag = off;
    		return 0;
    	}
    	else{
    		return -1;
    	}
    }
}
