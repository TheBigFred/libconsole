////////////////////////////////////////////////////////////////////////////////
// File      : options.cpp
// Contents  : unitests
//
// Author(s) : Frederic Gerard - mailfge@gmail.com
// URL       : https://github.com/TheBigFred/libconsole
//
//-----------------------------------------------------------------------------
// LGPL V3.0 - https://www.gnu.org/licences/lgpl-3.0.txt
//-----------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include <options.h>

class options_Fixture : public ::testing::Test
{
protected:
   enum {
      OPT_A=0,
      OPT_B,
      OPT_C,
      OPT_D,
      OPT_LA,
      OPT_LB,
      OPT_LC,
      OPT_LD,
      OPT_LE,
      OPT_LF,
      SUB_OPT_A,
      SUB_OPT_B,
      SUB_OPT_C,
      SUB_OPT_D,
      SUB_OPT_E,
      SUB_OPT_F,
   };

   console::options opt;

   void SetUp() override
   {
      opt.add("a",   console::options::arg::no,       OPT_A);
      opt.add("b",   console::options::arg::required, OPT_B);
      opt.add("c",   console::options::arg::optional, OPT_C);
      opt.add("d",   console::options::arg::optional, OPT_D);
      opt.add("--a", console::options::arg::no,       OPT_LA);
      opt.add("--b", console::options::arg::required, OPT_LB);
      opt.add("--c", console::options::arg::optional, OPT_LC);
      opt.add("--d", console::options::arg::optional, OPT_LD);
      opt.add("--e", console::options::arg::required, OPT_LE);
      opt.add("--f", console::options::arg::optional, OPT_LF);
      opt.add_suboption("--e","a", console::options::arg::no,       SUB_OPT_A);
      opt.add_suboption("--e","b", console::options::arg::required, SUB_OPT_B);
      opt.add_suboption("--e","c", console::options::arg::optional, SUB_OPT_C);
      opt.add_suboption("--f","d", console::options::arg::no,       SUB_OPT_D);
      opt.add_suboption("--f","e", console::options::arg::required, SUB_OPT_E);
      opt.add_suboption("--f","f", console::options::arg::optional, SUB_OPT_F);
   }

   void TearDown() override
   {
   }
};

TEST_F(options_Fixture, single_short_option)
{
   const char *arg[] = {
      "AppName",
      "-a", "titi",
      "-b", "toto",
      "-c",
      "-d", "tata"
   };

   int argc = sizeof(arg)/sizeof(arg[0]);
   auto rc = opt.parse(argc, (char**)arg);
   ASSERT_EQ(rc, 0);

   int res = 0;
   for (auto act : opt.actions_list)
   {
      switch (act.opt_code)
      {
         case OPT_A: ASSERT_EQ(act.opt_arg, "");      res++; break;
         case OPT_B: ASSERT_EQ(act.opt_arg, "toto");  res++; break;
         case OPT_C: ASSERT_EQ(act.opt_arg, "");      res++; break;
         case OPT_D: ASSERT_EQ(act.opt_arg, "tata");  res++; break;
         default:    ASSERT_TRUE(false);
      }
   }
   ASSERT_EQ(res,opt.actions_list.size());
}


TEST_F(options_Fixture, multi_short_option)
{
   const char *arg[] = {
      "AppName",
      "-acd", "titi",
      "-b", "toto"
   };

   int argc = sizeof(arg)/sizeof(arg[0]);
   auto rc = opt.parse(argc, (char**)arg);
   ASSERT_EQ(rc, 0);

   int res = 0;
   for (auto act : opt.actions_list)
   {
      switch (act.opt_code)
      {
         case OPT_A: ASSERT_EQ(act.opt_arg, "");     res++; break;
         case OPT_B: ASSERT_EQ(act.opt_arg, "toto"); res++; break;
         case OPT_C: ASSERT_EQ(act.opt_arg, "");     res++; break;
         case OPT_D: ASSERT_EQ(act.opt_arg, "");     res++; break;
         default:    ASSERT_TRUE(false);
      }
   }
   ASSERT_EQ(res,opt.actions_list.size());
}

TEST_F(options_Fixture, bad_short_option)
{
   const char *arg[] = {
      "AppName",
      "-aed",
   };

   int argc = sizeof(arg)/sizeof(arg[0]);
   auto rc = opt.parse(argc, (char**)arg);
   ASSERT_NE(rc, 0);
}

TEST_F(options_Fixture, missing_short_option)
{
   const char *arg[] = {
      "AppName",
      "-",
   };

   int argc = sizeof(arg)/sizeof(arg[0]);
   auto rc = opt.parse(argc, (char**)arg);
   ASSERT_EQ(rc, 0);
}

TEST_F(options_Fixture, long_option)
{
   const char *arg[] = {
      "AppName",
      "--a", "titi",
      "--b", "toto",
      "--c",
      "--d", "tata"
   };

   int argc = sizeof(arg)/sizeof(arg[0]);
   auto rc = opt.parse(argc, (char**)arg);
   ASSERT_EQ(rc, 0);

   int res = 0;
   for (auto act : opt.actions_list)
   {
      switch (act.opt_code)
      {
         case OPT_LA: ASSERT_EQ(act.opt_arg, "");      res++; break;
         case OPT_LB: ASSERT_EQ(act.opt_arg, "toto");  res++; break;
         case OPT_LC: ASSERT_EQ(act.opt_arg, "");      res++; break;
         case OPT_LD: ASSERT_EQ(act.opt_arg, "tata");  res++; break;
         default:    ASSERT_TRUE(false);
      }
   }
   ASSERT_EQ(res,opt.actions_list.size());
}

TEST_F(options_Fixture, bad_long_option)
{
   const char *arg[] = {
      "AppName",
      "--b"
   };

   int argc = sizeof(arg)/sizeof(arg[0]);
   auto rc = opt.parse(argc, (char**)arg);
   ASSERT_NE(rc, 0);
}

TEST_F(options_Fixture, sub_long_option)
{
   const char *arg[] = {
      "AppName",
      "--e", "a",
      "--e", "b", "z",
      "--e", "c",
      "--f",
      "--f", "d",
      "--f", "e", "z",
      "--f", "f"
   };

   int argc = sizeof(arg)/sizeof(arg[0]);
   auto rc = opt.parse(argc, (char**)arg);
   ASSERT_EQ(rc, 0);

   int res=0;
   for (auto act : opt.actions_list)
   {
      switch (act.opt_code)
      {
         case SUB_OPT_A: ASSERT_EQ(act.opt_arg, "");  res++; break;
         case SUB_OPT_B: ASSERT_EQ(act.opt_arg, "z"); res++; break;
         case SUB_OPT_C: ASSERT_EQ(act.opt_arg, "");  res++; break;
         case OPT_LF:    ASSERT_EQ(act.opt_arg, "");  res++; break;
         case SUB_OPT_D: ASSERT_EQ(act.opt_arg, "");  res++; break;
         case SUB_OPT_E: ASSERT_EQ(act.opt_arg, "z"); res++; break;
         case SUB_OPT_F: ASSERT_EQ(act.opt_arg, "");  res++; break;
         default:    ASSERT_TRUE(false);
      }
   }
   ASSERT_EQ(res,opt.actions_list.size());
}

TEST_F(options_Fixture, bad_sub_long_option)
{
   const char *arg[] = {
      "AppName",
      "--e", "b"
   };

   int argc = sizeof(arg)/sizeof(arg[0]);
   auto rc = opt.parse(argc, (char**)arg);
   ASSERT_NE(rc, 0);
}