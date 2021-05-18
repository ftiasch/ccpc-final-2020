#!/usr/bin/env python3
# Adapted from @Riatre

import typer
import pathlib
import zipfile

testlib = pathlib.Path(__file__).with_name("testlib.h")

def main(chal_path: pathlib.Path, output_path: pathlib.Path):
    chal_name = chal_path.name
    timelimit = None
    title = None
    for line in open(chal_path / 'statement.md').readlines():
        if line.startswith('timelimit:'):
            timelimit = int(line.rstrip().split(':')[1])
        if line.startswith('# '):
            title = line.split('# ')[1].strip()
    if timelimit is None:
        raise RuntimeError('No TL')
    if title is None:
        raise RuntimeError('No Title')
    z = zipfile.ZipFile(output_path, "w", zipfile.ZIP_DEFLATED)
    z.writestr("domjudge-problem.ini", '\n'.join([
        f"timelimit=\"{timelimit}\"",
    ]))
    z.writestr("problem.yaml", '\n'.join([
        f"name: {title}",
        "validation: custom",
    ]))
    for sample_ans in (chal_path / "samples").glob("*.a"):
        name = sample_ans.name[:-2]
        sample_in = sample_ans.with_name(name)
        z.write(sample_in, f"data/sample/{name}.in")
        z.write(sample_ans, f"data/sample/{name}.ans")
    for data_ans in (chal_path / "tests").glob("*.a"):
        name = data_ans.name[:-2]
        data_in = data_ans.with_name(name)
        z.write(data_in, f"data/secret/{name}.in")
        z.write(data_ans, f"data/secret/{name}.ans")
    for sol in chal_path.glob("solution*.cc"):
        z.write(sol, f"submissions/accepted/{sol.name}")
    for sol in chal_path.glob("slow*.cc"):
        z.write(sol, f"submissions/time_limit_exceeded/{sol.name}")
    for sol in chal_path.glob("wrong*.cc"):
        z.write(sol, f"submissions/wrong_answer/{sol.name}")
    z.write(testlib, f"output_validators/{chal_name}/testlib.h")
    z.write(chal_path / "check.cc", f"output_validators/{chal_name}/check.cc")

typer.run(main)
