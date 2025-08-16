global load_page_directory
global enable_paging

load_page_directory:
    mov cr3, eax
    ret

enable_paging:
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    ret

; kill me
; yes, this is being pushed
