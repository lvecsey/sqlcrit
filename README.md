
*Overview*

Use an SQLite DB with keyword strings and webpage mappings, converting to a critbit structure saved on disk. Query the critbit structure through FastCGI (nginx) and link to a list of matching webpages.

*Dependencies*

```console
sudo apt-get install libsqlite3-dev libfcgi-dev
```

*Compiling*

```console
make sqlcrit
```

*Structures*

See mapping_table.txt for the SQLite DB table to create. The insertion.txt has some sample insert statements.

*Running*

First run sqlite3 and paste or type the command to create the mapping table. Then insert a few values.
Finally, save and quit sqlite3 as shown below:


```
.save sqlite.db
.quit
```

Create the sqlcrit.txt critbit mapping file.

```
./sqlcrit sqlite.db > sqlcrit.txt.new
mv sqlcrit.txt.new sqlcrit.txt
```

*Installation*

Finally, compile the FastCGI example and connect it to your nginx webserver.

```
make sqlcrit-fastcgi
```

Run spawn-fcgi on a given port and have an nginx configuration to reach it.

You can use the included sqlcrit.html page to query the FastCGI endpoint.

*Automation*

If you modify the sqlcrit-fastcgi program, you can redeploy it with these steps.

- [ ] Sync the updated sources with the webserver, or dedicated FastCGI server.
- [ ] Recompile sqlcrit-fastcgi on the server.
- [ ] Restart the spawn-fcgi process.

*Learn more*

[Nginx](https://www.nginx.org)
