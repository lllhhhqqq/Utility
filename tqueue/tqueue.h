/** 
 * @file tqueue.h
 * @brief 简单说明
 * @sa 参考对象
 * @author Luhaoqing 
 * @date 21/5/2013
 *
 * 详细说明   
 */
#ifndef TQUEUE_H
#define TQUEUE_H

#define CHUNK_SIZE 1024

//环形队列, 加入原子操作， 实现一个impl
template <typename T, typename Alloc, int N>
class TQueue
{
public:
    TQueue(): buffer_(NULL),head_(NULL),alloc_(new Alloc(CalSize())) {}
    ~TQueue() {}

    static TQueue* GetInstance()
    {
        static TQueue<T, ShareMemoryImpl, N> queue;
        return &queue;
    }
private:
    template <typename T>
    struct HeadInfo
    {
        size_t read_pos;    //读偏移
        size_t write_pos;   //写偏移
        size_t read_ptr_pos;//读指针的偏移
        size_t write_ptr_pos;//写指针的偏移
        T* readptr;         //读指针
        T* writeptr;        //写指针
        //sync pos
        //
    };

    typedef HeadInfo<T> Head;

    template <typename T, int N>
    struct chunk
    {
        T* block[N];
        T* prev;
        T* next;
    };

    typedef chunk<T, N> chunk_st;

public:

    bool init()
    {
        bool ret = false;
        buffer_ = alloc_->Alloc(CalSize());
        if (NULL != buffer_)
        {
            FormatBuffer(false);
        }
        return ret;
    }

    template <typename _TyImpl>
    bool InitRead(_TyImpl& impl)
    {
        impl.InitBuffer((chunks_[head_->read_pos]->block[head_->read_ptr_pos][0]));
        return true;
    }

	template <typename _TyImpl>
	bool Read(_TyImpl& impl, size_t read_size)
	{
		//get readpos,to get readoffset 
		//impl.setbuffer buffer+readpos
		//readpos += readoffset;
		//return true;

		//size_t read_size = GetReadSize(chunks_[head_->read_pos]->block[head_->read_ptr_pos]);
		size_t read_block = CalBlock(read_size);

		//impl.setbuffer buffer+readpos
		updateReadPos(read_block);
		return true;
	}

	template <typename _TyImpl>
	bool Write(_TyImpl& impl)
	{
		//getwriteoffset
		//if write pos >= read pos writepos+writeoffset >= readpos
		//if writepos < readpos writepos + writeoffset < readpos
		//else return false
		//writepos += offset
		//impl.setbuffer buffer+writepos impl.setmaxsize writeoffset
		//return true;
		//TO DO,如果write位置在read后面 并且write到结束的位置都不够内存写入的 
		//直接从头上面计算可写内存 如果可写直接分配头上面的内存 保证内存块是连续并且够用的
		//后面的内存直接跳过 这样在写入内存的时候就不用再去检查内存大小什么的了

		size_t real_write_pos = head_->write_pos * N + head_->write_ptr_pos;
		size_t real_read_pos = head_->read_pos * N + head_->read_ptr_pos;
		size_t block_can_write = (real_write_pos >= real_read_pos) ? CalBlockCount() -real_write_pos + real_read_pos 
			: real_read_pos - real_write_pos;
		
		size_t write_offset = impl.GetWriteSize();
		size_t write_block = CalBlock(write_offset);

		if (write_block < block_can_write)
		{
			impl.InitBuffer((chunks_[head_->write_pos]->block[head_->write_ptr_pos][0]));
			updateWritePos(write_block);
		}
		else
			return false;

		return true;
	}

private:
	inline void updateWritePos(size_t blockcount)
	{
		size_t pos_offset = blockcount/N;
		size_t block_offset = blockcount%N;

		if (block_offset + head_->write_ptr_pos > N)
		{
			head_->write_pos = (head_->write_pos + pos_offset + 1)% CHUNK_SIZE;
			head_->write_ptr_pos = (head_->write_ptr_pos + block_offset)%N;
		}
		else
		{
			if (pos_offset != 0)
			{
				size_t postion = (head_->write_pos + pos_offset)%CHUNK_SIZE;
				head_->write_pos = postion;
			}
			head_->write_ptr_pos += block_offset;
		}
		
	}

	inline void updateReadPos(size_t blockcount)
	{
		size_t pos_offset = blockcount/N;
		size_t block_offset = blockcount%N;

		if (block_offset + head_->read_ptr_pos > N)
		{
			head_->read_pos = (head_->read_pos + pos_offset + 1)% CHUNK_SIZE;
			head_->read_ptr_pos = (head_->read_ptr_pos + block_offset)%N;
		}
		else
		{
			if (pos_offset != 0)
			{
				size_t postion = (head_->read_pos + pos_offset)%CHUNK_SIZE;
				head_->read_pos = postion;
			}
			head_->read_ptr_pos += block_offset;
		}
	}

    inline void FormatBuffer(bool init)
    {
        if ( 1 )
        {
            //整块内存清空
            memset (buffer_, 0, CalSize());
        }

        head_ = (Head*)buffer_;

        size_t head_offset = CalHeadSize();
        size_t chunk_size = sizeof(T*)*(N + 2);
        size_t chunk_offset = chunk_size * CHUNK_SIZE;

        chunk_st* ck = NULL,*prevck = NULL;
        
        for (size_t i = 0; i < CHUNK_SIZE; ++i)
        {
            //ck = (chunk_st*)(buffer_ + head_offset + CalChunk_OffSet(i));
            ck = (chunk_st*)(buffer_ + head_offset + chunk_size * i);

            for (size_t j = 0; j < N; ++j)
            {
                ck->block[j] = (T*)(buffer_ + head_offset + chunk_offset + CalChunk_OffSet(i) + sizeof(T)*j);
            }
            
            size_t prev_offset = (i == 0) 
                ? CalChunk_OffSet(CHUNK_SIZE - 1) 
                : CalChunk_OffSet(i - 1);

            size_t next_offset = (i == CHUNK_SIZE)
                ? CalChunk_OffSet(0)
                : CalChunk_OffSet(i + 1);

            ck->prev = (T*)(buffer_ + head_offset + chunk_offset + prev_offset);
            ck->next = (T*)(buffer_ + head_offset + chunk_offset + next_offset);
            chunks_[i] = ck;
        }
    }

    inline size_t CalHeadSize()
    {
        return sizeof(Head);
    }

    inline size_t CalSize() 
    {
        
        return CalHeadSize() + CalChunkSize() + sizeof(T) * CalBlockCount();
    }

    inline size_t CalChunkSize()
    {
        return sizeof(T*) * (N+2) * CHUNK_SIZE;
    }

    inline size_t CalBlockCount()
    {
        return N * CHUNK_SIZE;
    }

    inline size_t CalChunk_OffSet(size_t block_count) 
    {
        size_t size = -1;
        if (block_count < CHUNK_SIZE)
        {
            return sizeof(T) * N * block_count;
        }
        return size;
    }

	inline size_t CalBlock(size_t size)
	{
		return size/sizeof(T) + 1;
	}

    inline size_t CalChunk_TOTAL_OffSet(size_t size)
	{
		int count = CalBlock(size);
		return count * sizeof(T);
	}

	size_t GetReadSize(chunk_st* chunk);
private:
    chunk_st* chunks_[CHUNK_SIZE];
    Head* head_;
    char* buffer_;
    Alloc* alloc_;
};
#endif