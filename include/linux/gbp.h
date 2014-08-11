#define GBP_MAX_ENTRY_SLOTS	32

#include <linux/list.h>

struct gbp_session {
	struct mutex mutex;
	struct list_head bp_list;
	unsigned long bp_ids;

	unsigned long bp_slots;
	struct task_struct *blocked_task[GBP_MAX_ENTRY_SLOTS];
	spinlock_t entry_lock;
	wait_queue_head_t waitq;

	struct list_head node;
};

struct gbp_information {
	int fd;
	int ___pad0;
	u64 offset;
	char __pad1[16];
};

struct gbp_bp {
	struct uprobe_consumer uc;
	struct gbp_session *gbp_s;
	unsigned int bp_id;

	struct inode *inode;
	unsigned long offset;
	struct list_head node;
};

extern struct list_head gbp_sessions;
