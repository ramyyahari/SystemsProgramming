

sudo mount -o loop ../fdimage /mnt
sudo rm /mnt/bin/*
sudo umount /mnt

sh mku u1
sh mku u2
